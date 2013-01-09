#include <stdio.h>

int main()
{
    int p, e, i, d;
    int case_n = 0, next;

    while (scanf("%d%d%d%d", &p, &e, &i, &d) > 0
            && -1 != p) {
        next = (5544 * p + 14421 * e + 1288 * i - d) % 21252;
        next = next > 0 ? next : next + 21252;
        printf("Case %d: the next triple peak occurs in %d days.\n", 
                ++case_n, next);
    }
    return 0;
}
