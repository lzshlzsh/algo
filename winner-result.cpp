#include <stdio.h>


#define N 4


void calculate_result(int winner[N][N], int n, int order[N], int result[N])
{
	int i, j, tmp;
	for (i = 0; i < n; i++)
		result[i] = order[i];

	while (n >= 2){
		i = 0;
		for (j = 0; j < n - 1; j += 2){
			tmp = result[i];
			if (winner[result[j]][result[j + 1]] == result[j]){
				result[i] = result[j];
				result[j] = tmp;
			}else{
				result[i] = result[j + 1];
				result[j + 1] = tmp;
			}
			i++;
		}
		n >>= 1;
	}
}


int main()
{
	int winner[N][N] = {
		{0, 1, 2, 3},
		{1, 1, 2, 1},
		{2, 2, 2, 3},
		{3, 1, 3, 3},
	};
	int order[N] = {0, 1, 2, 3};
	int result[N];
	int i;

	calculate_result(winner, N, order, result);

	for (i = 0; i < N; i++){
		printf("%5d", result[i]);
	}
	printf("\n");
	return 0;
}
