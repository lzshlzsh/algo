#include <iostream>
#include <vector>
#include <cassert>
#include <iomanip>

using namespace std;

//#define DEBUG

class Node
{
public:
	vector<int> child;
	vector<int> query;
	int p;	
	int rank;
	int ancestor;
	int degree;
	bool finished;
};

class Tree
{
private:
	static const int MAX_NODES = 10001;
	int nb_node;
	Node node[MAX_NODES];
private:
	void init();
	void do_lca(const int u);
	inline void make_set(const int u);
	int find_set(const int u);
	inline void union_set(const int u, const int v);
	void internal_link(const int u, const int v);

public:

	Tree(): nb_node(0){};


	void construct_tree();

	void lca();

#ifdef DEBUG
	void print_tree()const;
#endif
};


#ifdef DEBUG
void Tree::print_tree()const
{
	for (int i = 1; i < nb_node; i++){
		cout << i << ": ";
		for (vector<int>::const_iterator it = node[i].child.begin();
				it != node[i].child.end(); it++){
			cout << setw(5) << *it;
		}
		cout << endl;
	}
}
#endif

void Tree::init()
{
	for (int u = 1; u <= nb_node; u++){
		node[u].child.clear();
		node[u].query.clear();
		node[u].p = 0;
		node[u].rank = 0;
		node[u].ancestor = 0;
		node[u].degree = 0;
		node[u].finished = false;

	}
}
void Tree::construct_tree()
{
	int u, v;
	cin >> nb_node;

	init();

	for (int j = 0; j < nb_node - 1; j++){
		cin >> u >> v; /*arc*/	
		node[u].child.push_back(v);
		node[v].degree++;
	}
	cin >> u >> v; /*query*/
	node[u].query.push_back(v);
	node[v].query.push_back(u);
}


void Tree::make_set(const int u)
{
	node[u].p = u;
	node[u].rank = 0;
}

int Tree::find_set(const int u)
{
	if (u != node[u].p){
		node[u].p = find_set(node[u].p);
	}
	return node[u].p;
}

void Tree::union_set(const int u, const int v)
{
	internal_link(find_set(u), find_set(v));
}

void Tree::internal_link(const int u, const int v)
{
	if (node[u].rank < node[v].rank){
		node[u].p = v;
	}else{
		node[v].p = u;
		if (node[u].rank == node[v].rank){
			node[u].rank++;
		}
	}
}

void Tree::do_lca(const int u)
{
	make_set(u);
	node[u].ancestor = u;

	for (vector<int>::iterator it = node[u].child.begin(); 
			it != node[u].child.end(); it++){
		do_lca(*it);
		union_set(u, *it);
		node[find_set(*it)].ancestor = u;
	}

	node[u].finished = true;

	for (vector<int>::iterator it = node[u].query.begin(); 
			it != node[u].query.end(); it++){
		if (node[*it].finished){
			cout << node[find_set(*it)].ancestor << endl;
		}
	}
}
void Tree::lca()
{
	for (int i = 1; i < nb_node; i++){
		if (0 == node[i].degree){
			do_lca(i);
		}
	}
}

int main()
{
	Tree tree;
	int nb_t;

	cin >> nb_t;

	for (int i = 0; i < nb_t; i++){
		tree.construct_tree();
#ifdef DEBUG
		tree.print_tree();
#endif
		tree.lca();
	}

	return 0;
}
