#include <iostream>

#define ELENUM 6

using namespace std;

int counter = 0;

void  stack_seq(int n, int m)
{
 if(n == 0)
 {
  counter++;
  return;
 }
 stack_seq(n-1,m+1);
 if (0 != m)
	 stack_seq(n,m-1);
}

int main(void)
{
 stack_seq(ELENUM,0);
 cout<<"the total is "<<counter<<endl;
 return 0;
}
