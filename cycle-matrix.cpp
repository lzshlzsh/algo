#include <iostream>
#include <iomanip>
#include <cassert>

using namespace std;

//#define DEBUG

int main()
{
	int number = 13;
	int cnt = 0;
	int i = 1, j, k, l, m, e;
	int **A;

	while (i < number){
		cnt++;
		i <<= 1;
	}
#ifdef DEBUG
	cout << "cnt = " << cnt << endl;
#endif

	A = new int *[cnt];
	assert(A);
	for (i = 0; i < cnt; i++){
		A[i] = new int[cnt];
		assert(A[i]);
	}

	i = (cnt - 1) >> 1;
	j = i;
	
	k = 1;
	A[i][j] = k++;
	m = 1;
	e = 1;

	while (k < number){
		for (l = 1; l <= m; l++){
			j += e;
			A[i][j] = k++;
		}
		for (l = 1; l <= m; l++){
			i += e;
			A[i][j] = k++;
		}
		m++;
		e = -e;
	}

	for (i = 0; i < cnt; i++){
		for (j = 0; j < cnt; j++){
			cout << setw(5) << A[i][j];
		}
		cout << endl;
	}

	
	for (i = 0; i < cnt; i++){
		delete [] A[i];
	}
	delete [] A;

	return 0;
}
