#include <iostream>
#include <stack>
#include <cstdlib>

using namespace std;

enum Action
{
	ACTION_A,
	ACTION_B,
	ACTION_AB,
	ACTION_A2B,
};

static void print_action(const int M, const int N, int &sum,
		const Action a, const bool a_larger)
{
	switch (a){
	case ACTION_A:
		cout << M << ", 0, " << sum << endl; 
		sum += M;
		cout << 0 << ", 0, " << sum << endl; 
		break;
	case ACTION_B:
		cout << "0, " << N << ", " << sum << endl; 
		sum += N;
		cout << "0, 0, " << sum << endl; 
		break;
	case ACTION_AB:
		if (a_larger){
			cout << M << ", 0, " << sum << endl; 
			cout << M - N << ", " << N << ", " << sum << endl; 
			sum += (M - N);
			cout << "0, " << N << ", " << sum << endl; 
		}else{
			cout << "0, " << N << ", " << sum << endl; 
			cout << M << ", " << N - M << ", " << sum << endl; 
			sum += (N - M);
			cout << M << ", " << 0 << ", " << sum << endl; 
		}
		cout << "0, 0, " << sum << endl;
		break;
	case ACTION_A2B:
		break;
	default:
		cout << "error in print_action" << endl;
		exit(-1);
	}
}
static void print_solution(const int M, const int N,
		stack<Action> &action, const bool a_larger)
{
	Action a;
	int sum = 0;
	while (!action.empty()){
		a = action.top();
		print_action(M, N, sum, a, a_larger);
		action.pop();
	}
}

static void try_to_fill(const int M, const int N, const int K, 
		stack<Action> &action, const bool a_larger)
{
	if (0 == K){
		print_solution(M, N, action, a_larger);
		exit(0);
	}else if (K < 0){
		return;
	}
	action.push(ACTION_A);
	try_to_fill(M, N, K - M, action, a_larger);
	action.pop();

	action.push(ACTION_B);
	try_to_fill(M, N, K - N, action, a_larger);
	action.pop();

	action.push(ACTION_AB);
	try_to_fill(M, N, K - (a_larger ? (M - N) : (N - M)), action, a_larger);
	action.pop();
}


static void simple_fill(const int M, const int K, stack<Action> &action)
{
	int tmp = K;
	while (tmp > 0){
		action.push(ACTION_A);
		tmp -= M;
	}
	if (0 == tmp){
		print_solution(M, M, action, 0);
	}else{
		cout << "No Solution" << endl;
	}
}

int main()
{
	const int M = 5, N = 7, K = 4;
	stack<Action> action;
	bool a_larger = (M > N);

	cout << M << ", " << N << ", " << K << endl;
	cout << "******************" << endl;
	cout << "0, 0, 0" << endl; /*all empty*/

	if (M == N){
		simple_fill(M, K, action);
		return 0;
	}

	try_to_fill(M, N, K, action, a_larger);

	action.push(ACTION_A2B);
	try_to_fill(M, N, K - (a_larger ? (2*N - M) : (2*M - N)), 
			action, a_larger);

	cout << "No Solution" << endl;

	return 0;
}
