#include <stdio.h>


int main()
{
//	const int A[] = {9, 5, 2, 4, 7};
	const int A[] = {1, 9, 5, 2, 4, 7};
	const int n = sizeof(A) / sizeof(int);
	int Idx[n]; /*Idx[0..i]: noincreasing order indices of 'A'*/
	int D[n];
	int i, j;
	
	/*init*/
	for (i = 0; i < n; i++){
		D[i] = -1;
	}
	i = -1;
	for (j = n - 1; j >= 0; j--){
		while(i >= 0 && A[j] > A[Idx[i]]){
			D[Idx[i]] = j;
			i--;
		}
		Idx[++i] = j;
	}

	for (i = 0; i < n; i++){
		printf("%5d", A[i]);	
	}
	printf("\n");
	for (i = 0; i < n; i++){
		printf("%5d", D[i]);	
	}
	printf("\n");

	return 0;
}
