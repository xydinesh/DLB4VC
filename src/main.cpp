#include "Node.h"
#include "Graph.h"
#include "DimacsGraphBuilder.h"
#include <iostream>

using namespace std;
using namespace dlb;

int main()
{
	cout << "dinesh" << endl;

	Node n;
	
	n.add_nbr(3);
	n.add_nbr(5);
	n.add_nbr(10);
	n.print();
	list<int> *nlist = n.get_nbrs();
	n.delete_nbr(3);
	n.delete_nbr(5);
	n.print();

	Graph g;
	for (int i = 0; i < 5; i++)
		g.add_node();

	g.add_edge(0, 1);
	g.add_edge(0, 4);
	g.add_edge(1, 4);
	g.add_edge(1, 2);
	g.add_edge(2, 3);
	g.add_edge(3, 4);
	g.print();

	cout << "Graph Operations" << endl;
	cout << "##############"<< endl;
	g.delete_node(4);
	g.delete_node(0);
	g.print();

	DimacsGraphBuilder db("C:/Users/Dinesh/DLB4VC/sh2-5.dim");
	db.build_graph();
	return 0;
}