#include <stdio.h>

#define N 4

static int solution_nb = 0;

static void print_layout(int A[N][N])
{
	int i, j;
	printf("***************\n");
	for (i = 0; i < N; i++){
		for (j = 0;j < N; j++){
			printf("%5d", A[i][j]);
		}
		printf("\n");
	}
}

static void n_quee(int A[N][N], int i, int has_quee[N])
{
	int j;
	if (i >= N){
		print_layout(A);	
		solution_nb++;
	}else{
		for (j = 0; j < N; j++){
			if (!has_quee[j]){
				has_quee[j] = 1;
				A[i][j] = 1;
				n_quee(A, i + 1, has_quee);
				has_quee[j] = 0;
			}
			A[i][j] = 0;
		}
	}
}


int main()
{
	int A[N][N] = {{0,},};
	int has_quee[N] = {0,};

	n_quee(A, 0, has_quee);

	printf("The number of total solutions: %d\n", solution_nb);

	return 0;
}
