#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

typedef unsigned int uint32;
typedef unsigned short uint16;
typedef unsigned long long uint64;

static uint32 *s_value[5] = {NULL, };
static int s_exp = 0;
static uint32 s_dummy0[1], s_dummy1[1 << 1], s_dummy2[1 << 2], 
              s_dummy3[1 << 3], s_dummy4[1 << 4];
static uint32 *s_mem[5] = {
    s_dummy0, s_dummy1, s_dummy2, s_dummy3, s_dummy4,
};

static void str2scientificexpr(const char *str)
{
    int len;
    uint32 val = 0;
    int exp = 1;
    int i;

    len = strlen(str) - 1;

    for (i = len; i >= 0; i--) {
        if ('.' == str[i]) {
            s_exp = i - len;
        } else {
            val += (str[i] - '0') * exp;
            exp *= 10;
        }
    }

    *s_mem[0] = val;
    s_value[0] = s_mem[0];
}

static inline void mul(uint32 *dst, uint32 src1, uint32 src2)
{
    uint32 h, l;
    __asm__ __volatile__ (
        "mull %3\n"
        : "=&d"(h), "=a"(l)
        : "1"(src1), "r"(src2)
        : "memory"
    );

    dst[1] = h;
    dst[0] = l;
}

static inline void add(uint32 *dst, uint32 v)
{
    __asm__ __volatile__ (
        "addl %0, (%1)\n"
        "adcl $0, 4(%1)\n"
        :
        : "r"(v), "r"(dst)
        : "memory"
    );
}

static inline void add_v(uint32 *dst, uint32 *v)
{
    add(dst, v[0]);
    if (v[1]) {
        add(&dst[1], v[1]);
    }
}

static void mul_v(uint32 *dst, int len, uint32 *src1, int len1, 
        uint32 *src2, int len2)
{
    uint32 tv[2];
    uint32 td[len];
    int i, j;

    memset(tv, 0, sizeof(tv));
    memset(td, 0, sizeof(td));
    for (i = 0; i < len1; i++) {
        for (j = 0; j < len2; j++) {
            if (src1[i] && src2[j]) {
                mul(tv, src1[i], src2[j]);
                add_v(&td[i + j], tv);
            }
        } 
    }
    memcpy(dst, td, len << 2);
}

static int done(const uint16 *tval, int *pj)
{
    int j;

    for (j = *pj; j >= 0; j--) {
        if (tval[j]) {
            *pj = j;
            return 0;
        }
    }
    *pj = j;
    return 1;
}

static void print_result(const uint32 *result, const int len, const int exp)
{
    char buf[128];
    uint16 tval[len << 1];
    int i, j, k = 0;
    uint32 t1, t2;
    
    memset(buf, 0, sizeof(buf));
    memcpy(tval, result, len << 2);

    for (j = (len << 1) - 1; !done(tval, &j); ){
        for (i = j, t2 = 0; i >= 0; i--) {
            t1 = ((t2 << 16) + tval[i]) / 10;
            t2 = ((t2 << 16) + tval[i]) % 10;
            tval[i] = (uint16)t1;
        }
        buf[k++] = (char)t2 + '0';
    }
    
    if (!strlen(buf)) {
        printf("0\n");
        return;
    }

    if (0 == exp){
        j = 0;
        goto direct;
    } else if (exp < 0) {
        for (j = 0; j < -exp && '0' == buf[j]; j++);
        if (j >= -exp) {
            goto direct;
        }
        if (k <= -exp) {
            printf(".");
            for (i = 0; i < -exp - k; i++) {
                printf("0");
            }
            goto direct;
        } else {
            for (i = k - 1; i > -exp - 1; i--, k--) {
                printf("%c", buf[i]);
            }
            printf(".");
            goto direct;
        }
    } else {
        for (i = k - 1; i >= j; i--) {
            printf("%c", buf[i]);
        }
        for (i = 0; i < exp; i++) {
            printf("0");
        }
        printf("\n");
    }

    return;
direct:
    for (i = k - 1; i >= j; i--) {
        printf("%c", buf[i]);
    }
    printf("\n");
}

static void do_compute_exp(int exp, int lvl)
{
    uint32 *pv;

    if (exp <= 1) {
        return;
    }

    pv = s_value[lvl + 1] = s_mem[lvl + 1];
    memset(pv, 0, 1 << (lvl + 3));
    
    mul_v(pv, 1 << (lvl + 1), s_value[lvl], 1 << lvl, s_value[lvl], 1 << lvl);
    if (!(exp & 0x1)){
        s_value[lvl] = NULL;
    }
    do_compute_exp(exp >> 1, lvl + 1);
}

static void compute_exp(int exp)
{
    int i;
    uint32 result[1 << 4];
    int flag = 0;

    if (1 == exp) {
        print_result(s_value[0], 1, s_exp);
        return;
    }

    do_compute_exp(exp, 0); 

    memset(result, 0, sizeof(result));
    for (i = 4; i >= 0; i--) {
        if (s_value[i]) {
            if (!flag) {
                memcpy(result, s_value[i], 1 << (i + 2));
                flag = 1;
            } else {
                mul_v(result, 1 << 4, result, 1 << 4, s_value[i], 1 << i);
            }
            s_value[i] = NULL;
        }
    }
    print_result(result, 1 << 4, s_exp * exp);
}

int main()
{
    char str[8];
    int exp;

#if 0
    while (scanf("%s%d", str, &exp) > 0) {
       str2scientificexpr(str); 
       compute_exp(exp);
    }
#else    
    int i;

    memset(str, 0, sizeof(str));
    for (i = 1; i < 99999; i++) {
        fprintf(stderr, "%d\n", i);
        snprintf(str, 7, "%f", i / 1000.0);
        for (exp = 1; exp <= 25; exp++) {
            str2scientificexpr(str); 
            compute_exp(exp);
        }
    }
#endif

    return 0;
}

