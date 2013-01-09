/*
 * two sorted arrays, find the intersection of them
 */
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

#define N1 10
#define N2 20
#define MAX 10
#define DEBUG 

static int i_compare(const void *i, const void *j)
{
	return *(const int *)i - *(const int *)j;
}

int main()
{
	int A[N1];
	int B[N2];
	const int N = (N1 < N2) ? N1 : N2;
	int C[N];
	int i, j, k;

	srandom((unsigned int)time(NULL));
#if 1
	for (i = 0; i < N1; i++){
		A[i] = random() % MAX;
	}
	for (i = 0; i < N2; i++){
		B[i] = random() % MAX;
	}
	qsort(A, N1, sizeof(A[0]), i_compare);
	qsort(B, N2, sizeof(B[0]), i_compare);
#endif

#ifdef DEBUG
	for (i = 0; i < N1; i++){
		printf("%4d", A[i]);
	}
	printf("\n");
	for (i = 0; i < N2; i++){
		printf("%4d", B[i]);
	}
	printf("\n");
#endif
	i = 0; 
	j = 0;
	k = 0;
	while (i < N1 && j < N2){
		if (A[i] < B[j]){
			i++;
		}else if (A[i] == B[j]){
			if (k > 0){
				if (A[i] != C[k - 1]){
					C[k++] = A[i];
				}
			}else{
				C[k++] = A[i];
			}
			i++;
			j++;
		}else{
			j++;
		}
	}

	printf("intersection(%d):\n", k);
	for (i = 0; i < k; i++){
		printf("%4d", C[i]);
	}
	printf("\n");

	return 0;
}
