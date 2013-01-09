#include <stdio.h>
#include <string.h>

static void compute_period(int D[], char *P, int m)
{
	int i, j;

	D[0] = 1;
	i = 0;
	j = 1;
	while (j < m){
		if (P[i] == P[j]){
			D[j] = j - i;
			i++;
			j++;
		}else if (0 == i){
			D[j] = j + 1;
			j++;
		}else{
			i = i - D[i - 1];
		}
	}
}

static void kmp(char *T, int n, char *P, int m, int *D)
{
	int i, j;
	i = 0;
	j = 0;
	while (j - i <= n - m){
		if (P[i] == T[j]){
			i++;
			j++;
		}else if (0 == i){
			j++;
		}else{
			i = i - D[i - 1];
		}
		if (i == m){
			printf("[%d, %d]match\n", j - m, j - 1);
			i = i - D[i - 1];
		}
	}
}

int main()
{
	char *T = "acabaabaabcacaabaabcac";
	char *P = "abaabcac";
	int n = strlen(T);
	int m = strlen(P);
	int i;

	int D[m];

	compute_period(D, P, m);
#if 1
	for (i = 0; i < n; i++){
		printf("%5i", i);
	}
	printf("\n");
	for (i = 0; i < n; i++){
		printf("%5c", T[i]);
	}
	printf("\n");
	for (i = 0; i < m; i++){
		printf("%5c", P[i]);
	}
	printf("\n");
	for (i = 0; i < m; i++){
		printf("%5d", D[i]);
	}
	printf("\n");
#endif

	kmp(T, n, P, m, D);

	return 0;
}
