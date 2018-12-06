#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STICK_NUM 64

static int s_n, s_len, s_ulen;
static char s_sticks[MAX_STICK_NUM];
static char s_visit[MAX_STICK_NUM];

static int cmp(const void *a, const void *b)
{
    return *(char *)b - *(char *)a;
}

static int dfs(int ulen, int index, int len)
{
    int i;

    if (len == s_len) {
        return 1;
    }

    for (i = index; i < s_n; i++) {
        if (s_visit[i] || (i > index && !s_visit[i - 1] 
                    && s_sticks[i] == s_sticks[i - 1])) {
            continue;
        }
        s_visit[i] = 1;
        if (ulen + s_sticks[i] == s_ulen) {
            if (dfs(0, 0, len + s_ulen)) {
                return 1;
            }
            s_visit[i] = 0;
            return 0;
        } else if (ulen + s_sticks[i] < s_ulen) {
            if (dfs(ulen + s_sticks[i], i + 1, len)) {
                return 1;
            }
        }
        s_visit[i] = 0;
        if (!ulen) {
            return 0;
        }
    }
    return 0;
}

static int solve()
{
    qsort(s_sticks, s_n, sizeof(s_sticks[0]), cmp);

    for (s_ulen = s_sticks[0]; s_ulen < s_len; s_ulen++) {
        if (s_len % s_ulen) {
            continue;
        }
        memset(s_visit, 0, sizeof(s_visit));
        if (dfs(0, 0, 0)) {
            return s_ulen;
        }
    }
    return s_len;
}

int main()
{
    int i, unit;

    while (scanf("%d", &s_n) > 0 && s_n) {
        s_len = 0;
        for (i = 0; i < s_n; i++) {
            scanf("%d", &unit);
            s_sticks[i] = (char)unit;
            s_len += s_sticks[i];
        }
        printf("%d\n", solve());
    }
    return 0;
}

