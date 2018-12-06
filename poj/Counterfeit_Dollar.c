#include <stdio.h>
#include <ctype.h>

#define MAX_DOL 12

static char s_even[MAX_DOL];
static char s_noteven[MAX_DOL];

static void solve(const char **str)
{
    int 

    switch (str[2][0]) {
        case 'e':
            break;
        case 'u':
        case 'd':
            break;
        default:
            break;
    }
}

int main()
{
    int n, i, j;
    char str[3][8];

    scanf("%d", &n);

    while (n-- > 0) {
        for (j = 0; j < 3; j++) {
            for (i = 0; i < 3; i++) {
                scanf("%s", str[i]);
            }
            solve(str);
        }
    }

    return 0;
}

