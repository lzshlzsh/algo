#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DEBUGON
#ifdef DEBUGON
# define trace printf
#else
# define trace(arg...) 
#endif

struct element_t {
    int *value;
    int len;
    int exp;
    int height;
};

static int parse_base(const char *base, 
        struct element_t *value)
{
    char *dot;
    int i, j, len;
    int exp;
    
    value->len = 1;
    value->value = (int *)malloc(sizeof(int));
    if (!value->value) {
        perror("malloc");
        return -1;
    }
    *value->value = 0;

    len = strlen(base);
    if ((dot = strchr(base, '.'))){
        /* e.g. 12.345 */
        value->exp = -(len - 1 - (dot - base));
        for (exp = 1, i = len - 1; i >= 0; i--) {
            if ('.' != base[i]) {
                *value->value += exp * (base[i] - '0');
                exp *= 10;
            }
        }
    } else {
        value->exp = 0;
        for (j = 0; j < len && '0' == base[j]; j++);
        for (exp = 1, i = len - 1; i >= j; i--) {
            *value->value += exp * (base[i] - '0');
            exp *= 10;
        }
    }

    trace("value = %d, exp = %d\n", *value->value, value->exp);
    return 0;
}

static void cal_result(const char *base, 
        const unsigned int exp)
{
    int h;
    struct element_t value[5];

    trace("%s %2d\n", base, exp); 

    if (parse_base(base, &value[0]) < 0) {
        return;
    }

    for (h = exp; h > 1; h >>= 1) {
        
    }
}

int main()
{
    char base[8];
    unsigned int exp;
    while (2 == scanf("%s%d", base, &exp)){
        cal_result(base, exp);
    }
    return 0;
}
