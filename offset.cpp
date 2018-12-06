#include <iostream>

using namespace std;

struct A{
	int a;
	bool b;
	short f;
	short cr:5;
	short cg:6;
	short cb:5;
	float s;
};

#define offsetof(type, name) __builtin_offsetof(type, name)

int main()
{
	A a __attribute((__aligned(4)));
	cout << (size_t)&((A *)0)->f << endl;
	cout << offsetof(A, a) << endl;
	cout << offsetof(A, b) << endl;
	cout << offsetof(A, f) << endl;
/*	cout << offsetof(A, cr) << endl;
	cout << offsetof(A, cg) << endl;
	cout << offsetof(A, cb) << endl;*/
	cout << offsetof(A, s) << endl;
	cout << sizeof(A) << endl;
	return 0;
}
