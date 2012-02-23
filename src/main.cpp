#include "Node.h"
#include "Graph.h"
#include "BuilderFactory.h"
#include <iostream>
#include <stdio.h>
#include "log.h"
using namespace std;
using namespace dlb;

int main()
{
	cout << "dinesh" << endl;
    char x[100];
    char xe[100];
    sprintf(x, "graph.log");
    sprintf(xe, "graph.log");
    // 1: debug , 5: critical
    LOG_INIT(x, xe, 1);

	Node n;
	
	n.add_nbr(3);
	n.add_nbr(5);
	n.add_nbr(10);
	n.print();
	const list<int> *nlist = n.get_nbrs();
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

	BuilderFactory f;
	Graph *ng;
	string gt("dimacs");
	Builder *b = f.create_builder(gt);
	b->set_filename("../sh2-5.dim");
	ng = b->build_graph();

    //delete ng;
    DEBUG("starting plane.dim graph\n");
    b->set_filename("../plane.dim");
    ng = b->build_graph();

    DEBUG("nodes: %d\n", ng->get_nnodes());
    cout << ng->get_nnodes() << endl;

    ng->delete_edge(11, 12);
    ng->delete_node(12);

    DEBUG("nodes: %d\n", ng->get_nnodes());
    for (int i = 0; i < ng->get_nnodes(); i++)
    {
        cout << i << ":";
        for (int j = 0; j < ng->get_nnodes(); j++)
        {

            if (ng->is_edge(i, j))
            {
                cout << j << " ";
            }
        }
        cout << endl;
    }
    LOG_CLOSE();
	return 0;
}
