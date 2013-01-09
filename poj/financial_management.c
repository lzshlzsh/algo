#include <stdio.h>

int main()
{
    int i;
    float f, t;

    for (i = 0, f = 0.0; i < 12; i++) {
       scanf("%f", &t); 
       f += t;
    }

    printf("$%.2f\n", f / 12.0);

    return 0;
}

