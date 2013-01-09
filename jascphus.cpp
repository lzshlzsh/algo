/**
 *	Created Time: 2009-11-10 09:21:19
 *	Last Modified: 2009-11-10 09:21:19
 *	File Name: jascphus.cpp
 *	Description: 
 */
#include <iostream>
using namespace std;

static int jascphus(int n , int m)
{
//	m = m % n;
	return ((n == 1) ? 1 : 
		((m = (jascphus(n - 1, m) + m) % n) ? m : n));
}
int main()
{
//	int n = 7;
	int m = 65;
	cout << "intput n and m to compute J(n, m)" << endl;
/*	cout << "n:";
	cin >> n;
	cout << "m:";
	cin >> m;*/
	for (int i = 1; i < 64; i++){
	  cout << "J(" << i << ", " << m << ") = " << jascphus(i, m) << endl;
	  if (!((i + 1) & i))
		cout << "---------------" << endl;
	}
	return 0;
}
