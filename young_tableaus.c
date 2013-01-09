/*
 * Introduction to Algorithm Chapter 6 
 * Problems: 6-3 Young tableaus
 */
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define INFINITE (int)((unsigned int)(1 << 31) - 1)

#define MAX_M 32
#define MAX_N 32


static int M = 4; 
static int N = 4;


static int Y[MAX_M][MAX_N]/* = {
	{2, 3, 4, 5}, {8, 9, 12, 14}, 
	{16, INFINITE, INFINITE, INFINITE}, 
	{INFINITE, INFINITE, INFINITE, INFINITE}
}*/;

#define DEBUG

static void tableaus_maintain_max(int i, int j)
{
	int min_i, min_j;
	if (i < M - 1 && Y[i][j] > Y[i + 1][j]){
		min_i = i + 1;
		min_j = j;
	}else{
		min_i = i;
		min_j = j;
	}
	if (j < N - 1 && Y[min_i][min_j] > Y[i][j + 1]){
		min_i = i;
		min_j = j + 1;
	}
	
	if (!(min_i == i && min_j == j)){
		/*exchange Y[i][j] <-> Y[min_i][min_j]*/
		Y[i][j] = Y[i][j] ^ Y[min_i][min_j];
		Y[min_i][min_j] = Y[i][j] ^ Y[min_i][min_j];
		Y[i][j] = Y[i][j] ^ Y[min_i][min_j];
		tableaus_maintain_max(min_i, min_j);
	}
}

/*c*/
static int extract_min()
{
	int min = Y[0][0];
	
	Y[0][0] = INFINITE;

	tableaus_maintain_max(0, 0);

	return min;
}

static inline int do_search(int i, int j, int e)
{
	int ret = INFINITE;

	if (Y[i][j] == e)
		return e;
	if (e < Y[i][j])
		return INFINITE;

	if (i < M - 1)
		ret = do_search(i + 1, j, e);
	if (INFINITE == ret && j < N - 1)
		ret = do_search(i, j + 1, e);
	return ret;
}

/*f*/
static int search(int e)
{
	return do_search(0, 0, e);
}


static void tableaus_maintain_min(int i, int j)
{
	int max_i, max_j;
	
	if (i > 0 && Y[i][j] < Y[i - 1][j]){
		max_i = i - 1;
		max_j = j;
	}else{
		max_i = i;
		max_j = j;
	}
	if (j > 0 && Y[max_i][max_j] < Y[i][j - 1]){
		max_i = i;
		max_j = j - 1;
	}
	if (!(max_i == i && max_j == j)){
		/*exchange Y[i][j] <-> Y[max_i][max_j]*/
		Y[i][j] = Y[i][j] ^ Y[max_i][max_j];
		Y[max_i][max_j] = Y[i][j] ^ Y[max_i][max_j];
		Y[i][j] = Y[i][j] ^ Y[max_i][max_j];
		tableaus_maintain_min(max_i, max_j);
	}
}

/*d*/
static void insert(int e)
{
	Y[M - 1][N - 1] = e;
	tableaus_maintain_min(M - 1, N - 1);
}

#ifdef DEBUG
static void print_tableau()
{
	int i, j;
	for (i = 0; i < M; i++){
		for (j = 0; j < N; j++){
			if (INFINITE == Y[i][j])
				printf(" INFI");
			else
				printf("%5d", Y[i][j]);
		}
		printf("\n");
	}
	printf("*********************\n");
}
#endif

/*e*/
static void sort()
{
	int i;
	for (i = 0; i < M * N; i++){
		/*XXX: for simplicity, we only print the sorted values, 
		 * we can put them to an array to get what we want
		 */
		printf("%5d", extract_min());
		if ((i % N) == N - 1)
			printf("\n");
	}
}

int main()
{
	int i, j;
	for (i = 0; i < MAX_M; i++){
		for (j = 0; j < MAX_N; j++){
			Y[i][j] = INFINITE;
		}
	}
	insert(9);
	insert(16);
	insert(3);
	insert(2);
	insert(4);
	insert(8);
	insert(5);
	insert(14);
	insert(12);
#ifdef DEBUG
	print_tableau();
#endif
	
	for (i = 1; i < 17; i++){
		if (INFINITE == search(i)){
			printf("%d NOT found\n", i);
		}else{
			printf("%d found\n", i);
		}
	}

	printf("extract_min: %d\n", extract_min());
#ifdef DEBUG
	print_tableau();
#endif

	M = 16;
	N = 16;
	srandom((unsigned int)time(NULL));

	for (i = 0; i < M; i++){
		for (j = 0; j < N; j++){
			insert(random() % (M * N));
		}
	}

#ifdef DEBUG
	print_tableau();
#endif
	sort();
	return 0;
}
