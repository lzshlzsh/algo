#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;


void func(int A[], int j, int n, vector<int> &stk, vector<int> &que)
{
	static int cnt = 0;
	if (j >= n){
		cout << ++cnt << ": ";
		for (unsigned int k = 0; k < que.size(); k++){
			cout << setw(5) << que[k];
		}
		for (int k = stk.size() - 1; k >= 0; k--){
			cout << setw(5) << stk[k];
		}
		cout << endl;
		return;
	}
	stk.push_back(A[j]); /*enter stack*/
	func(A, j + 1, n, stk, que); /*left subtree*/
	stk.pop_back(); /*return to current*/

	if (!stk.empty()){ /*pop stack*/
		que.push_back(stk.back());
		stk.pop_back();
		func(A, j, n, stk, que); /*right subtree*/
		stk.push_back(que[que.size() - 1]);	
		que.pop_back();
	}
}


int main()
{
	int A[] = {1, 2, 3};
	vector<int> stk;
	vector<int> que;
	
	func(A, 0, sizeof(A) / sizeof(int),	stk, que);
 
	return 0;
}
