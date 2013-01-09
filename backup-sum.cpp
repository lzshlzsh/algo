#include <iostream>
#include <iomanip>

using namespace std;


/*
 * give M and an array A[], output the indices of 
 * A[] such that the sum of the corresponding elements is M
 *
 * solution: backup search method
 */

#define DEBUG


static int partion(int A[], int idx[], const int r, 
		const int t)
{
	int i, j, tmp;
	for (i = r - 1, j = r; j < t; j++){
		if (A[j] <= A[t]){
			i++;
			if (i != j){
				tmp = A[i];
				A[i] = A[j];
				A[j] = tmp;
				tmp = idx[i];
				idx[i] = idx[j];
				idx[j] = tmp;
			}
		}
	}
	i++;
	if (i != j){
		tmp = A[i];
		A[i] = A[j];
		A[j] = tmp;
		tmp = idx[i];
		idx[i] = idx[j];
		idx[j] = tmp;
	}
	return i;
}
static void quick_sort(int A[], int idx[], const int r, 
		const int t)
{
	int s;
	if (r < t){
		s = partion(A, idx, r, t);
#if 0//def DEBUG
		for (int i = 0; i < 4; i++){
			cout << setw(5) << idx[i]; 
		}
		cout << endl;
#endif
		quick_sort(A, idx, r, s - 1);
		quick_sort(A, idx, s + 1, t);
	}
}

void print_solution(const int A[], const int X[], const int idx[],
		const int number)
{
	cout << "get solution" << endl;
	for (int i = 0; i < number; i++){
		if (X[i]){
			cout << setw(5) << idx[i] << "(" << A[i] << ")";
		}
	}
	cout << endl;
}

void get_solution(int s, int k, int r, const int M, 
		const int A[], const int idx[], int X[], 
		const int number)
{
	X[k] = 1;
	if (M == s + A[k]){
		print_solution(A, X, idx, number);
	}else if (k + 1 < number && s + A[k] + A[k + 1] <= M){
		get_solution(s + A[k], k + 1, r - A[k], M, A, idx, X, number);
	}
	
	if (s + r - A[k] >= M && (k + 1 < number && s + A[k + 1] <= M)){
		X[k] = 0;
		get_solution(s, k + 1, r - A[k], M, A, idx, X, number);
	}

}

int main()
{
	int A[] = {11, 13, 24, 7};
	const int M = 31;
	int number = sizeof(A) / sizeof(int);
	
	int idx[number];
	int X[number];
	int sum;

#ifdef DEBUG
	for (int i = 0; i < number; i++){
		cout << setw(5) << A[i]; 
	}
	cout << endl;
#endif
	for (int i = 0; i < number; i++){
		idx[i] = i;
		X[i] = 0;
	}
	quick_sort(A, idx, 0, number - 1);
#ifdef DEBUG
	for (int i = 0; i < number; i++){
		cout << setw(5) << A[i]; 
	}
	cout << endl;
	for (int i = 0; i < number; i++){
		cout << setw(5) << idx[i]; 
	}
	cout << endl;
#endif

	sum = 0;
	for (int i = 0; i < number; i++){
		sum += A[i];
	}
	get_solution(0, 0, sum, M, A, idx, X, number);
	return 0;
}
