#include <iostream>
#include <iomanip>

using namespace std;


static void swap(int &a, int &b)
{
	int tmp = a;
	a = b;
	b = tmp;
}

static void bubbysort(int A[], int i, const int n)
{
	bool exchanged = false;
	if (i == n)
		return;

	for (int j = n - 1; j >= i; j--){
		if (A[j] > A[j + 1]){
			swap(A[j], A[j + 1]);
			exchanged = true;
		}
	}
	if (exchanged){
		bubbysort(A, i + 1, n);
	}
}

int main()
{
	int A[] = {3, 4, 9, 1, 10, 5, 4};

	bubbysort(A, 0, sizeof(A) / sizeof(int) - 1);
	
	for (unsigned int i = 0; i < sizeof(A) / sizeof(int); i++)
		cout << setw(5) << A[i];
	cout << endl;

	return 0;
}

