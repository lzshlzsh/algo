#include <stdio.h>
#include <string.h>

struct clock_t {
    int clock0 : 2;
    int clock1 : 2;
    int clock2 : 2;

    int clock3 : 2;
    int clock4 : 2;
    int clock5 : 2;

    int clock6 : 2;
    int clock7 : 2;
    int clock8 : 2;

    int dummy : 14;
};

static struct clock_t s_moves[9] = {
/*  {A, B, C, D, E, F, G, H, I, dummy, }, */
    {1, 1, 0, 1, 1, 0, 0, 0, 0, 0, },
    {1, 1, 1, 0, 0, 0, 0, 0, 0, 0, },
    {0, 1, 1, 0, 1, 1, 0, 0, 0, 0, },

    {1, 0, 0, 1, 0, 0, 1, 0, 0, 0, },
    {0, 1, 0, 1, 1, 1, 0, 1, 0, 0, },
    {0, 0, 1, 0, 0, 1, 0, 0, 1, 0, },

    {0, 0, 0, 1, 1, 0, 1, 1, 0, 0, },
    {0, 0, 0, 0, 0, 0, 1, 1, 1, 0, },
    {0, 0, 0, 0, 1, 1, 0, 1, 1, 0, },
};
static struct clock_t s_clocks;
static int s_shortest_seq = 0x7fffffff;
static int s_trace[9] = {0, };
static int s_answer[9] = {0, };

static void clockwise(int i)
{
    s_clocks.clock0 += s_moves[i].clock0;
    s_clocks.clock1 += s_moves[i].clock1;
    s_clocks.clock2 += s_moves[i].clock2;

    s_clocks.clock3 += s_moves[i].clock3;
    s_clocks.clock4 += s_moves[i].clock4;
    s_clocks.clock5 += s_moves[i].clock5;

    s_clocks.clock6 += s_moves[i].clock6;
    s_clocks.clock7 += s_moves[i].clock7;
    s_clocks.clock8 += s_moves[i].clock8;
    
    s_trace[i]++;
}

static void counter_clockwise(int i)
{
    s_clocks.clock0 -= s_moves[i].clock0;
    s_clocks.clock1 -= s_moves[i].clock1;
    s_clocks.clock2 -= s_moves[i].clock2;

    s_clocks.clock3 -= s_moves[i].clock3;
    s_clocks.clock4 -= s_moves[i].clock4;
    s_clocks.clock5 -= s_moves[i].clock5;

    s_clocks.clock6 -= s_moves[i].clock6;
    s_clocks.clock7 -= s_moves[i].clock7;
    s_clocks.clock8 -= s_moves[i].clock8;

    s_trace[i]--;
}

static int check_answer(int j)
{
    if (j >= s_shortest_seq) {
        return 1;
    }

    if (0 == *(int *)&s_clocks) {
        memcpy(s_answer, s_trace, sizeof(s_trace));
        s_shortest_seq = j;
        return 1;
    }

    return 0;
}

static void solve(int i, int j)
{
    if (i >= 9) {
        return;
    }

    if (check_answer(j)) {
        goto ret0;
    } 
    solve(i + 1, j);

    clockwise(i);
    if (check_answer(j + 1)) {
        goto ret1;
    } 
    solve(i + 1, j + 1);

    clockwise(i);
    if (check_answer(j + 2)) {
        goto ret2;
    } 
    solve(i + 1, j + 2);

    clockwise(i);
    if (check_answer(j + 3)) {
        goto ret3;
    } 
    solve(i + 1, j + 3);

ret3:    
    counter_clockwise(i);
ret2:    
    counter_clockwise(i);    
ret1:
    counter_clockwise(i);    
ret0:
    return;
}

int main()
{
    int hr;
    int i;

    *(int *)&s_clocks = 0;
    scanf("%d", &hr);
    s_clocks.clock0 = hr & 0x3;
    scanf("%d", &hr);
    s_clocks.clock1 = hr & 0x3;
    scanf("%d", &hr);
    s_clocks.clock2 = hr & 0x3;

    scanf("%d", &hr);
    s_clocks.clock3 = hr & 0x3;
    scanf("%d", &hr);
    s_clocks.clock4 = hr & 0x3;
    scanf("%d", &hr);
    s_clocks.clock5 = hr & 0x3;

    scanf("%d", &hr);
    s_clocks.clock6 = hr & 0x3;
    scanf("%d", &hr);
    s_clocks.clock7 = hr & 0x3;
    scanf("%d", &hr);
    s_clocks.clock8 = hr & 0x3;

    solve(0, 0);

    for (i = 0; i < 9; i++) {
        while (s_answer[i]--) {
            printf("%d ", i + 1);
        }
    }
    printf("\n");
    return 0;
}

