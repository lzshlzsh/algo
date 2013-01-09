/*
 * the number of element 'e' is more than the number of array 'A',
 * find 'e'
 */

#define DEBUG

#include <stdio.h>

int main()
{
	int A[] = {1, 3, 4, 5, 3, 3, 4, 3, 3, 3};
	int e, i, j;

	e = A[0];
	i = 1;
#ifdef DEBUG	
	for (j = 0; j < sizeof(A) / sizeof(int); j++){
		printf("%5d", A[j]);
	}
	printf("\n");
#endif

	j = 1; 
	while (j < sizeof(A) / sizeof(int)){
#ifdef DEBUG		
		printf("start: j = %d, i = %d, e = %d\n", j, i, e);
#endif
		if (e == A[j]){
			i++;
			j++;
		}else{
			i--;
			if (0 == i){
				i = 1;
				j++;
				e = A[j];
			}
			j++;
		}
#ifdef DEBUG		
		printf("end: j = %d, i = %d, e = %d\n", j, i, e);
#endif
	}
	printf("e = %d\n", e);
	return 0;
}




