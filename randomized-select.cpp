#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cstring>
#include <iomanip>

using namespace std;

//#define DEBUG

static inline int random_range(const int p, const int r)
{
	return (int)(p + (float)random() / RAND_MAX * (r - p));
}


static int randomized_partion(int A[], const int p, const int r)
{
	int pivot;
	int q, i, j;

	q = random_range(p, r);
#ifdef DEBUG
	cout << "[" << p << ", " << r << "]: " << q << endl;
#endif
	swap(A[q], A[r]);
	pivot = A[r];
	
	for (i = p - 1, j = p; j < r; j++){
		if (A[j] <= pivot){
			i++;
			if (i != j){
				swap(A[i], A[j]);
			}
		}
	}
	i++;
	if (r != i){
		swap(A[i], A[r]);
	}
	return i;
}


static int randomized_select(int A[], const int p, const int r, 
		const int i)
{
	int q, k;

#ifdef DEBUG
	cout << setw(5) << "p, r, i = " << p << setw(5 )<< r 
		<< setw(5) << i << endl;
#endif
	if (p == r){
		return A[p];
	}
	
	q = randomized_partion(A, p, r);
	k = q - p + 1;

#ifdef DEBUG
	cout << "p, q, r, i = " << setw(5) << p << setw(5)
		<< q << setw(5 )<< r 
		<< setw(5) << i << endl;
#endif
	if (i == k){
		return A[q];
	}else if (i < k){
		return randomized_select(A, p, q - 1, i);
	}else{
		return randomized_select(A, q + 1, r, i - k);
	}


}

int main()
{
	int A[] = {4, 1, 2, 5, 3, 8, 7, 9, 10, 6};
	int N = sizeof(A) / sizeof(int);
	int T[N];

	srandom((unsigned int)time(NULL));

	for (int i = 1; i <= N; i++){
		memcpy(T, A, sizeof(A));
		cout << randomized_select(T, 0, N - 1, i) << endl;
	}
	return 0;
}
