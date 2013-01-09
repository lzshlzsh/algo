#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <assert.h>

//#define DEBUG

#define N 50

int main()
{
	int a[N];
	int i, ti;

	srandom((unsigned int)time(NULL));

	for (i = 0; i < N; i++)
		a[i] = i;

#ifdef DEBUG
	for (i = 0; i < N; i++){
		printf("%5d", a[i]);
		if (i % 10 == 9)
			printf("\n");
	}
	printf("\n");
#endif

	for (i = 0; i < N; i++){
		ti = (random() % (N - i)) + i;
		assert(ti >= i && ti < N);
#if 1//ndef DEBUG
		/*BUG: when i == ti*/
		if (i != ti){
			a[ti] = a[ti] ^ a[i];
			a[i] = a[ti] ^ a[i];
			a[ti] = a[ti] ^ a[i];
		}
#else
		if (i != ti){
			int t;
			t = a[ti];
			a[ti] = a[i];
			a[i] = t;
		}
#endif
#ifdef DEBUG
		{
			int j;
			printf("%d: ", ti);
			for (j = 0; j < N; j++){
				printf("%5d", a[j]);
				if (j % 10 == 9)
					printf("\n");
			}
			printf("\n**********\n");
		}
#endif
	}

#if 1//def DEBUG
	for (i = 0; i < N; i++){
		printf("%5d", a[i]);
		if (i % 10 == 9)
			printf("\n");
	}
	printf("\n");
#endif
	return 0;
}
