#include <iostream>
using namespace std;

class A{
public:	
	virtual void f(int i){cout << "f1" << endl;}
	void f(float f){cout << "f2" << endl;}
	void g(int i){cout << "f3" << endl;}
};

class B : public A{
public:	
	void f(int i){cout << "f4" << endl;}
	void f(float f){cout << "f5" << endl;}
	void g(int i){cout << "f6" << endl;}
};

int main()
{
	A *p = new B;
	p->f(1);
	p->f(1.0f);
	p->g(1);
	return 0;
}

