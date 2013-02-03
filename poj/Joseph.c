#include <stdio.h>

#define MAX_K 13

static int s_solution[MAX_K] = {0, };

static int f(int i, int n, int m)
{
    if (1 == i) {
        return (m - 1) % n + 1;
    }
    return (f(i - 1, n - 1, m) + m - 1) % n + 1;
}

static int is_solution(int k, int m)
{
    int i;

    for (i = 1; i <= k; i++) {
        if (f(i, k << 1, m) <= k) {
            return 0;
        }
    }
    return 1;
}

static int compute_m(int k)
{
    int m, i, t;

    for (t = 0; ; t++) {
        for (i = k + 1; i <= (k << 1); i++) {
            m = (k << 1) * t + i;
            if (is_solution(k, m)) {
                return m;
            }
        }
    }
    return 0;
}

int main()
{
    int k;

    while (scanf("%d", &k) > 0 && k) {
        printf("%d\n", s_solution[k - 1] ? 
                s_solution[ k - 1] :
                (s_solution[k - 1] = compute_m(k)));
    }
    return 0;
}

