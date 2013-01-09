#include <iostream>
#include <stack>

using namespace std;


enum Color 
{
	C_WHITE,
	C_GRAY,
	C_BLACK,
};
class Node;
class Arch
{
public:
	Node *node;
	Arch *next;
	Arch(): node(NULL), next(NULL){}
	Arch(Node *const node, Arch *const next = NULL): 
		node(node), next(next){}
	Arch(const Arch &ar): node(ar.node), next(ar.next){}
	~Arch(){}
};
class Node
{
public:
	char key;
	Color color;	
	int d, f;
	char pi;
	Arch *arch;
	Arch *cur;
public:
	Node(const char key, const Color color = C_WHITE, 
			const int d = -1, const int f = -1,
			const char pi = '\0', Arch *const arch = NULL): 
			key(key), color(color), d(d), f(f),
			pi(pi), arch(arch){}
	Node():key('\0'), color(C_WHITE), d(-1), f(-1),
			pi('\0'), arch(NULL){}

	~Node(){}
};


static void build_graph(Node *const g)
{
	Arch *ar;
	ar = g[0].arch = new Arch(&g[1]);
	ar = ar->next = new Arch(&g[3]);
	g[0].cur = g[0].arch;

	ar = g[1].arch = new Arch(&g[2]);
	ar = ar->next = new Arch(&g[3]);
	g[1].cur = g[1].arch;

	ar = g[2].arch = new Arch(&g[4]);
	g[2].cur = g[2].arch;

	ar = g[3].arch = new Arch(&g[4]);
	g[3].cur = g[3].arch;

	ar = g[4].arch = new Arch(&g[1]);
	g[4].cur = g[4].arch;

	ar = g[5].arch = new Arch(&g[6]);
	ar = ar->next = new Arch(&g[7]);
	g[5].cur = g[5].arch;

	ar = g[6].arch = new Arch(&g[0]);
	ar = ar->next = new Arch(&g[3]);
	g[6].cur = g[6].arch;

	ar = g[7].arch = new Arch(&g[5]);
	ar = ar->next = new Arch(&g[6]);
	g[7].cur = g[7].arch;
}

static void print_graph(Node *const g)
{
	Arch *ar;
	for (int i = 0; i < 8; i++){
		ar = g[i].arch;
		cout << g[i].key << ": ";
		while (ar){
			cout << ar->node->key << " ";
			ar = ar->next;
		}
		cout << endl;
	}
}
static void dfs_visit(Node *const g, Node *v)
{
	static int time = 0;
	stack<Node *> s;
	Node *u;
	Arch *ar;
	bool all_visited;

	v->d = ++time;
	v->color = C_GRAY;
	s.push(v);
	
	cout << "DFS: " << v->key << "(" << v->d << ") ";

	while (!s.empty()){
		all_visited = true;	

		u = s.top();
		ar = u->cur;
		while (ar){
			if (C_WHITE == ar->node->color){
				ar->node->color = C_GRAY;
				ar->node->d = ++time;
				ar->node->pi = u->key;
				u->cur = ar->next; /*for the next iteration*/
				s.push(ar->node);
				cout << ar->node->key << "(" << ar->node->d << u->key << ") ";
				all_visited = false;
				break;
			}
			ar = ar->next;
		}
		if (all_visited){
			u->cur = u->arch; /*restore*/
			u = s.top();
			s.pop();
			u->color = C_BLACK;
			u->f = ++time;
			cout << u->key << "(" << u->f << ") ";
		}
	}

	cout << endl;
}

static void dfs_no_recursive(Node *const g)
{

	for (int i = 0; i < 8; i++){
		if (C_WHITE == g[i].color){
			dfs_visit(g, &g[i]);
		}
	}
	
}
int main()
{
	Node g[8] = {
		Node('s'), /*0*/
		Node('z'), /*1*/
		Node('y'), /*2*/
		Node('w'), /*3*/
		Node('x'), /*4*/
		Node('t'), /*5*/
		Node('v'), /*6*/
		Node('u'), /*7*/
	};

	build_graph(g);
#if 1
	print_graph(g);
#endif

	dfs_no_recursive(g);

	return 0;
}
