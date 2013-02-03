#include <stdio.h>
#include <stdlib.h>

#define MAX_TYPE_NB 64

static char s_type[MAX_TYPE_NB];
static int s_type_nb = 0;

static char s_search[4];
static char s_result[4];
static char s_rlen;
static int s_request;
static char s_max_tn;
static char s_tie = 0;

static void print_result()
{
    int i;

    printf("%d", s_request);
    if (!s_rlen) {
        printf(" ---- none\n");
        return;
    }
    printf(" (%d):", s_max_tn);
    if (s_tie) {
        printf(" tie\n");
        return;
    }
    for (i = 0; i < s_rlen; i++) {
        printf(" %d", s_result[i]);
    }
    printf("\n");
}

static int stop(int si, char tn, int acc)
{
    int i;
    char m1, m2;

    if (acc > s_request) {
        return 1;
    }
    if (acc < s_request) {
        return 0;
    }

    /* acc eq */
    if (tn < s_max_tn) {
        return 1;
    }

    if (tn > s_max_tn) {
        goto save;
    }
    
    /* tn eq */
    if (si > s_rlen) {
        return 1;
    }

    if (si < s_rlen) {
        goto save;
    }

    /* si eq */
    for (i = 0, m1 = 0, m2 = 0; i < si; i++) {
        if (s_search[i] > m1) {
            m1 = s_search[i];
        }
        if (s_result[i] > m2) {
            m2 = s_result[i];
        }
    }
    if (m1 > m2) {
        goto save;
    }
    if (m1 < m2) {
        return 1;
    }

    /* m1 eq m2, tie */
    s_tie = 1;
    return 1;

save:
    s_tie = 0;
    s_rlen = si;
    s_max_tn = tn;
    for (i = 0; i < si; i++) {
        s_result[i] = s_search[i];
    } 
    return 1;
}

static void solve(int ti, int si, int tn, int acc)
{
    int i, j;

    if (ti >= s_type_nb || si >= 4) {
        return;
    }

    tn++;
    for (i = 0, j = 4 - si; i < j; i++) {
        s_search[si++] = s_type[ti];
        acc += s_type[ti];
        if (stop(si, tn, acc)) {
            break;
        }
    }
    if (j == i) {
        i--;
    }

    for (j = 0; j <= i; j++) {
        s_search[--si] = 0;
        acc -= s_type[ti];
        if (j == i) {
            tn--;
        }
        solve(ti + 1, si, tn, acc);
    }
}

int main()
{
    int dig, ret;
    
repeat:
    s_type_nb = 0;
    while ((ret = scanf("%d", &dig)) > 0 && dig > 0) {
        s_type[s_type_nb++] = (char)dig;
    }

    if (ret < 0) {
        return 0;
    }
    while (scanf("%d", &s_request) && s_request > 0) {
        s_rlen = 0;
        s_max_tn = 0;
        solve(0, 0, 0, 0);
        print_result();
    }
    
    goto repeat;

    return 0;
}
