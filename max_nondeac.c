#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

#define DEBUG

#define MAX_ELEMENT_NUM 100


static int search_first_larger(const int *idx, const int *A, 
		const int e, const int number)
{
	int l = 0, r = number - 1;
	int m = (l + r) / 2;
	while (l <= r){
		if (A[idx[m]] <= e){
			l = m + 1;
		}else{
			r = m - 1;
		}
		m = (l + r) / 2;
	}

	return l;
}

static void print_array(const int *A, const int *path, 
		const int i)
{
	if (-1 == path[i]){
		printf("%5d", A[i]);
	}else{
		print_array(A, path, path[i]);
		printf("%5d", A[i]);
	}
}

static void max_nondeac(const int *A, const int el_num)
{
	int idx_kept[el_num];/*index set kept*/
	int path[el_num]; /*predecessor of each element*/
	int idx_kept_num = 0; /*the number of index kept*/
	int i, larger;

	idx_kept[idx_kept_num++] = 0;
	path[0] = -1;

	for (i = 1; i < el_num; i++){
		/*larger: idx of idx_kept*/
		if ((larger = search_first_larger(idx_kept, A, A[i], idx_kept_num)) < idx_kept_num){
			/*del and insert*/
			if (0 == larger){
				path[i] = -1;
			}
			else{
				path[i] = idx_kept[larger - 1];
			}
			idx_kept[larger] = i;
		}else{
			path[i] = idx_kept[idx_kept_num - 1];
			idx_kept[idx_kept_num] = i;
			idx_kept_num++;
		}
	}
	
	printf("the number of max no-decreasing subarray is %d\n", idx_kept_num);
	print_array(A, path, idx_kept[idx_kept_num - 1]);
	printf("\n");
#ifdef DEBUG	
	printf("path:\n");
	for (i = 0; i < el_num; i++){
		printf("%5d", path[i]);
	}
	printf("\n");

	printf("idx_kept:\n");
	for (i = 0; i < idx_kept_num; i++){
		printf("%5d", idx_kept[i]);
	}
	printf("\n");
#endif
}


/*
 * f = max{f(i) | 0 <= i < n}
 * f(i) = 1 + max{0, f(j) | A[j] <= A[i], 0 <= j < i}
 */
static void max_nondeac_n2(const int *A, const int el_num)
{
	int f[el_num], max_f;
	int path[el_num];
	int i, j, tmp;

	f[0] = 1;
	path[0] = -1;

	for (i = 1; i < el_num; i++){
		max_f = 0;
		for (j = 0; j < i; j++){
			if (A[j] <= A[i]){
				if (max_f < f[j]){
					max_f = f[j];
					tmp = j;
				}
			}
		}

		f[i] = max_f + 1;
		if (max_f){
			path[i] = tmp;
		}else{
			path[i] = -1;
		}
	}
	
	max_f = 0;
	for (i = 0; i < el_num; i++){
		if (max_f < f[i]){
			max_f = f[i];
			tmp = i;
		}
	}
	printf("the number of max no-decreasing subarray is %d\n", max_f);
	print_array(A, path, tmp);
	printf("\n");
#ifdef DEBUG	
	printf("path:\n");
	for (i = 0; i < el_num; i++){
		printf("%5d", path[i]);
	}
	printf("\n");
#endif
}


int main()
{
	FILE *file;
	int A[MAX_ELEMENT_NUM];
	int i, el_num;

	file =  fopen("./max_nondeac.input", "r");
	if (!file){
		perror("fopen");	
		exit(1);
	}

	for (i = 0; i < MAX_ELEMENT_NUM; i++){
		if (EOF == fscanf(file, "%d", &A[i]))
			break;
#ifdef DEBUG 
		printf("%5d", A[i]);
#endif
	}
	el_num = i;
#ifdef DEBUG 
	printf("\n");
	for (i = 0; i < el_num; i++){
		printf("%5d", i);
	}
	printf("\n");
	printf("element number %d\n", el_num);
#endif

	max_nondeac(A, el_num);
	printf("*************************************\n");
	max_nondeac_n2(A, el_num);

	fclose(file);
	return 0;
}
