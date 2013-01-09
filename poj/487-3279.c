#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

static int *s_tel = NULL;
static int s_entrynb = 0;
static char s_telmap[26] = {
#define I(a) ((a) - 'A')    
    [I('A') ... I('C')] = 2,
    [I('D') ... I('F')] = 3,
    [I('G') ... I('I')] = 4,
    [I('J') ... I('L')] = 5,
    [I('M') ... I('O')] = 6,
    [I('P') ... I('S')] = 7,
    [I('T') ... I('V')] = 8,
    [I('W') ... I('Y')] = 9,
#undef I
};
static inline int mem2dig(char c) 
{
    return isdigit(c) ? c - '0' : s_telmap[c - 'A'];
}

static void read_allentry(int nb)
{
    int i, j, dig, exp;
    char buf[16];
    
    for (i = 0; i < nb; i++) {
        scanf("%s", buf);
        for (j = strlen(buf) - 1, dig = 0, exp = 1; 
                j >= 0; j--) {
            if ('-' != buf[j]) {
                dig += mem2dig(buf[j]) * exp;
                exp *= 10;
            }
        }
        s_tel[s_entrynb++] = dig;
    }
}

static int comp(const void *t1, const void *t2)
{
    return *(int *)t1 - *(int *)t2;
}

static void print_result()
{
    int i, j;
    char buf[16];
    int dupnb, tel, printnb = 0;

    qsort(s_tel, s_entrynb, sizeof(s_tel), comp);
    for (i = 0; i < s_entrynb; i++) {
        for (tel = s_tel[i], dupnb = 1; 
                i < s_entrynb - 1 && tel == s_tel[i + 1]; 
                i++, dupnb++);
        if (dupnb > 1) {
            snprintf(buf, sizeof(buf), "%07d", tel);
            for (j = 6; j >= 3; j--) {
                buf[j + 1] = buf[j];
            }
            buf[++j] = '-';
            buf[8] = '\0';
            printf("%s %d\n", buf, dupnb);
            printnb++;
        }
    } 
    if (!printnb) {
        printf("No duplicates.\n");
    }
}

int main()
{
    int nb;

    scanf("%d", &nb);
    s_tel = malloc(nb * sizeof(s_tel[0]));
    assert(s_tel);
    memset(s_tel, 0, nb * sizeof(s_tel[0]));
    read_allentry(nb);
    print_result();
    free(s_tel);

    return 0;
}

