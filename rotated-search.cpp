#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>

using namespace std;


static void left_rotate_1(int A[], const int N)
{
	int tmp = A[0];
	for (int i = 0; i < N - 1; i++){
		A[i] = A[i + 1];
	}
	A[N - 1] = tmp;
}


static int binary_search(const int A[], int l, int r, const int val)
{
	int m;
	while (l <= r){
		m = (l + r) >> 1;
		if (val == A[m])
			return m;
		else if (val < A[m])
			r = m - 1;
		else
			l = m + 1;
	}
	return -1;
}

static int rotated_search(const int A[], const int N, 
		const int val)
{
	int l, r, m;

	l = 0; 
	r = N - 1;

	cout << "searching " << val << endl;



	while (l <= r){
		m = (l + r) >> 1;

		if (A[l] < A[r]){
			/*case 4*/
			return binary_search(A, l, r, val);
		}

		if (val == A[m])
			return m;
		else if (A[l] > A[m]){
			/*case 1*/
			if (val > A[m] && val <= A[r])
				return binary_search(A, m + 1, r, val);
			else 
				r = m - 1;
		}else{
			/*case 2 and 3*/
			if (m == r || A[m] > A[m + 1]){
				/*case 2*/
				l = binary_search(A, l, m - 1, val);
				if (-1 != l)
					return l;
				return binary_search(A, m + 1, r, val);
			}else{
				/*case 3*/
				if (val >= A[l] && val < A[m]){
					return binary_search(A, l, m - 1, val);
				}else{
					l = m + 1;
				}
			}
		}
	}
	return -1;
}

static inline void case_test(const int val)
{
	cout << "get" << setw(5) << val << endl;
}

static void print_array(const int A[], const int N)
{
	cout << "index:";
	for (int i = 0; i < N; i++){
		cout << setw(5) << i;
	}
	cout << endl;
	cout << "array:";
	for (int i = 0; i < N; i++){
		cout << setw(5) << A[i];
	}
	cout << endl;
}

static int int_compare(const void *p1, const void *p2)
{
	return (*(const int *)p1 - *(const int *)p2);
}

int main()
{
	const int N = 8;
	int A[N] = {4, 4, 5, 6, 7, 2, 3, 4};/* = {6, 1, 5, 5, 5, 3, 6, 4};*/
	
	srandom((unsigned int)time(NULL));

	print_array(A, N);
	case_test(rotated_search(A, N, 5));

	for (int i = 0; i < N; i++)
		A[i] = random() % N;

	qsort(A, N, sizeof(int), int_compare);
	
	print_array(A, N);
	case_test(rotated_search(A, N, 3));
	case_test(rotated_search(A, N, random() % N));
	case_test(rotated_search(A, N, random() % N));
	case_test(rotated_search(A, N, random() % N));

	left_rotate_1(A, N);

	print_array(A, N);
	case_test(rotated_search(A, N, random() % N));
	case_test(rotated_search(A, N, random() % N));
	case_test(rotated_search(A, N, random() % N));
	case_test(rotated_search(A, N, random() % N));

	left_rotate_1(A, N);
	left_rotate_1(A, N);

	print_array(A, N);
	case_test(rotated_search(A, N, random() % N));
	case_test(rotated_search(A, N, random() % N));
	case_test(rotated_search(A, N, random() % N));
	case_test(rotated_search(A, N, random() % N));

	return 0;
}
