#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

#define OUT_PAIR_NUM_INC 2

typedef struct rle_pair_t {
    int value;
    int len;
}rle_pair_t;

static rle_pair_t s_in_pair[1000];
static int s_in_nb, s_w, s_h;

static rle_pair_t *s_out_pair = NULL;
static int s_out_size = 0, s_out_nb;

static void print_result()
{
    int i, len;

    len = 0;
    for (i = 1; i < s_out_nb; i++) {
        if (s_out_pair[i].value != s_out_pair[i - 1].value) {
            printf("%d %d\n", s_out_pair[i - 1].value, s_out_pair[i].len - len);
            len = s_out_pair[i].len;
        }
    }
    if (s_out_nb > 0) {
        printf("%d %d\n", s_out_pair[s_out_nb - 1].value, s_in_pair[s_in_nb - 1].len - len);
    }
    printf("0 0\n");
}

static inline int inside(int x, int y)
{
    return x >= 0 && x < s_w && y >= 0 && y < s_h;
}

static int binary_search(rle_pair_t *pair, int size, int len, int *reti)
{
    int min, max, mid;

    min = 0;
    max = size - 1;
    while (min <= max) {
        mid = (min + max) >> 1;
        if (pair[mid].len == len) {
            *reti = mid;
            return 1;
        } else if (len < pair[mid].len) {
            max = mid - 1;
        } else {
            min = mid + 1;
        }
    }
    *reti = min;
    return 0;
}

static inline int find_out_pair(int x, int y, int *reti)
{
    return binary_search(s_out_pair, s_out_nb, y * s_w + x, reti);
}

static void insert_out_pair(int k, int val, int len)
{
    if (s_out_nb >= s_out_size) {
        s_out_size += OUT_PAIR_NUM_INC;
        s_out_pair = realloc(s_out_pair, s_out_size * sizeof(rle_pair_t));
        assert(s_out_pair);
    }
    if (k < s_out_nb) {
        memmove(&s_out_pair[k + 1], &s_out_pair[k], 
                sizeof(s_out_pair[0]) * (s_out_nb - k));
    }
    s_out_pair[k].value = val;
    s_out_pair[k].len = len;
    s_out_nb++;
}

static inline int pixel(int x, int y)
{
    int k;

    return binary_search(s_in_pair, s_in_nb, y * s_w + x, &k) ?
        s_in_pair[k + 1].value :
        s_in_pair[k].value;
}

static int cal_value(int x, int y)
{
    int i, j, cur, val, max = 0;

    cur = pixel(x, y);
    for (i = x - 1; i <= x + 1; i++) {
        for (j = y - 1; j <= y + 1; j++) {
            if (!(i == x && j == y) && inside(i, j)) {
                val = cur - pixel(i, j);
                if (val < 0) {
                    val = -val;
                }
                if (max < val) {
                    max = val;
                }
            }
        }
    }
    return max;
}

static void dispose_pixel(int x, int y)
{
    int i, j, k;

    for (i = x - 1; i <= x + 1; i++) {
        for (j = y - 1; j <= y + 1; j++) {
            if (inside(i, j) && !find_out_pair(i, j, &k)) {
                insert_out_pair(k, cal_value(i, j), j * s_w + i);
            }
        }
    }
}

int main()
{
    int i, val, repeat, len;

    s_out_pair = malloc(OUT_PAIR_NUM_INC * sizeof(rle_pair_t));
    assert(s_out_pair);
    s_out_size = OUT_PAIR_NUM_INC;

    while (scanf("%d", &s_w) > 0 && s_w > 0) {
        printf("%d\n", s_w);
        s_in_nb = 0;
        s_out_nb = 0;
        len = 0;
        while (scanf("%d%d", &val, &repeat) > 0
                && (val + repeat) > 0) {
            s_in_pair[s_in_nb].value = val;
            len += repeat;
            s_in_pair[s_in_nb].len = len;
            s_in_nb++;
        }
        s_h = len / s_w;
        for (i = 0, len = 0; i < s_in_nb; len = s_in_pair[i].len, i++) {
            dispose_pixel(len % s_w, len / s_w);
        }
        print_result();
    }
    printf("0\n");

    free(s_out_pair);
    return 0;
}

