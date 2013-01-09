#include <stdio.h>

//#define AAA

int main()
{
    float fs;
    int i;
#ifdef AAA
    float f;
#endif    

#ifdef AAA    
    while (scanf("%f", &f) > 0) {
        if (f <= 0.0) {
            break;
        }
#endif        
        for (i = 1, fs = 0.5; fs <= 5.20; fs += 1.0/(i++ + 2)){
#ifndef AAA
            printf("%f, ", fs);
            if (!(i % 6)) {
                printf("\n");
            }
#else
            if (fs >= f) {
                printf("%d card(s)\n", i);
                break;
            }
#endif            
        }
#ifdef AAA    
    }
#endif

#ifndef AAA    
    printf("%f,", fs);
#endif
    printf("\n");

    return 0;
}

