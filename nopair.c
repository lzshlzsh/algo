#include <stdio.h>

int main()
{
	int A[] = {11, 2, 3, 2, 1, -1, 1, 11, 3};
	int e, i;

	e = 0;
	for (i = 0; i < sizeof(A) / sizeof(int); i++){
		e ^= A[i];
	}

	printf("%d\n", e);

	return 0;
}
