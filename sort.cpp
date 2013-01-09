#include <sys/time.h>
#include <iostream>
#include <cstdio>
#include <cstdlib>
using namespace std;

class Sort
{
	private:
		void insert_Sort(long *const A, const int n);
		void insert_Sort(const int n);

		void merge_Sort(const int n);


		void validate(long * const A, long * const A_sorted, const int n);
		void prepare(long *const A, long *const A_to, const int n);
		void print_time(const struct timeval &start, const struct timeval &end);

	public:

		void Start();
};
/*======================================================*/
void Sort::insert_Sort(long *const A, const int n)
{
}
void Sort::insert_Sort(const int n)
{
	struct timeval start, end;
	long A[n], A_sorted[n];

	prepare(A, A_sorted, n);

//	cout << "insertion sort begins...  ";
	
	gettimeofday(&start, NULL);
	insert_Sort(A, n);
	gettimeofday(&end, NULL);

	validate(A, A_sorted, n);

	print_time(start, end);
}
void Sort::merge_Sort(const int n)
{
}
/*======================================================*/
void Sort::validate(long * const A, long * const A_sorted, const int n)
{
}

void Sort::prepare(long *const A, long *const A_to, const int n)
{

}
void Sort::print_time(const struct timeval &start, const struct timeval &end)
{
}

void Sort::Start()
{
	int n = 10;
	for (int i = 1; i <= 6; i++){
		insert_Sort(n);
		merge_Sort(n);
		n *= 10;
	}
}


int main()
{
	Sort sort;
	sort.Start();
	return 0;
}
