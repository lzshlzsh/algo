#include <stdio.h>

int main()
{
    int n, i;
    float x, y;

    scanf("%d", &n);
    for (i = 1; i <= n; i++) {
        scanf("%f%f", &x, &y);
        printf("Property %d: This property will begin eroding in year %d.\n", 
                i, (int)(3.1415926 * (x * x + y * y) / 100 + 1.0));
    }
    printf("END OF OUTPUT.\n");

    return 0;
}

