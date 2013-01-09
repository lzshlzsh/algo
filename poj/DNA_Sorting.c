#include <stdio.h>
#include <string.h>

int main()
{
    int n, m, i, j, a, c, g, t;
    int max = 0;

    scanf("%d%d", &n, &m);
    
    char dna[m][n + 1];
    char idx[m];
    int unsortedness[m];

    for (i = 0; i < m; i++) {
       scanf("%s", dna[i]); 
       unsortedness[i] = 0;
       a = 0;
       c = 0;
       g = 0;
       t = 0;
       for (j = n - 1; j >= 0; j--) {
           switch (dna[i][j]) {
               case 'A':
                   a++;
                   break;
               case 'C':
                   c++;
                   unsortedness[i] += a;
                   break;
               case 'G':
                   g++;
                   unsortedness[i] += a + c;
                   break;
               case 'T':
                   t++;
                   unsortedness[i] += a + c + g;
                   break;
               default:
                   break;
           }
       }
       if (max < unsortedness[i]) {
           max = unsortedness[i];
       }
    }

    int nb[max + 1];

    memset(nb, 0, sizeof(nb));
    for (i = 0; i < m; i++) {
        nb[unsortedness[i]]++;
    }
    for (i = 1; i <= max; i++) {
        nb[i] += nb[i - 1];
    }

    for (i = m - 1; i >= 0; i--) {
        idx[nb[unsortedness[i]] - 1] = (char)i; 
        nb[unsortedness[i]]--;
    }

    for (i = 0; i < m; i++) {
        printf("%s\n", dna[(int)idx[i]]);
    }

    return 0;
}
