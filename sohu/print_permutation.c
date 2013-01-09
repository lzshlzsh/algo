/*
 * give an array of six elements: 1, 2, 2, 3, 4, 5
 * print all the permutations of the array such that:
 * 4 cannot be in the place of 3
 * 3 is not adjacent to 5
 *
 * ANSWER: the number of permutations is 198
 */
#include <stdio.h>
#include <stdlib.h>

#define DEBUG

static int A[] = {1, 2, 2, 3, 4, 5};
static int B[] = {0, 0, 0, 0, 0, 0};
const static int N = sizeof(A) / sizeof(A[0]);
static int first2_idx;
#ifdef DEBUG
static int cnt = 0;
#endif



static void f(const int i)
{
	int j;
	if (i >= N){
#ifdef DEBUG
		printf("%d: ", ++cnt);
#endif
		for (j = 0; j < N; j++){
			printf("%d", B[j]);
		}
		printf("\n");
		return;
	}

	for (j = 0; j < N; j++){
		/*4 is not int the place of 3*/
		if (4 == i && 2 == j)
			continue;
		/*3 is not adjacent to 5*/
		if (3 == i && ((j > 0 && 5 == B[j - 1]) ||
					(j < N - 1 && 5 == B[j + 1]))){
			continue;
		}
		/*5 is not adjacent to 3*/
		if (5 == i && ((j > 0 && 3 == B[j - 1]) ||
					(j < N - 1 && 3 == B[j + 1]))){
			continue;
		}
		/*dispose two 2s*/
		if (2 == i && j < first2_idx){
			continue;
		}
		if (0 == B[j]){
			/*keep the index of the first 2*/
			if (1 == i){
				first2_idx = j;
			}
			B[j] = A[i];
			f(i + 1);
			B[j] = 0;
		}
	}
}
int main()
{
	f(0);
	return 0;
}
