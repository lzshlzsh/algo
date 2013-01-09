#include <stdio.h>
#include <stdlib.h>

static int binary_search_first(const int *A, const int n, const int key)
{
	int l = 0, r = n - 1, m = (n - 1) / 2;
	while (l <= r){
		if (A[m] < key)
			l = m + 1;
		else
			r = m - 1;
		m = (l + r) / 2;
	}
	return l;
}
static int binary_search_last(const int *A, const int n, const int key)
{
	int l = 0, r = n - 1, m = (n - 1) / 2;
	while (l <= r){
		if (A[m] > key)
			r = m - 1;
		else
			l = m + 1;
		m = (l + r) / 2;
	}
	return r;
}

int main(int argc, char **argv)
{
	const int A[] = {0, 0, 0, 2, 3, 3, 3, 3, 3, 4, 5, 5};
	int l, r, key, n;
	
	if (argc != 2){
		printf("Usage: %s key\n", argv[0]);
		return 1;
	}

	key = atoi(argv[1]);
	n = sizeof(A) / sizeof(int);
	/*0 <= l <= n*/
	l = binary_search_first(A, n, key);	
	if (l >= n || key != A[l]){
		printf("%d not found\n", key);
		return 0;
	}
	/*-1 <= r <= n -1*/
	r = binary_search_last(A, n, key);	
	if (l > r){
		printf("%d not found\n", key);
	}else{
		printf("%d occurs %d times\n", key, r - l + 1);
	}

	return 0;
}
