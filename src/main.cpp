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
	BuilderFactory f;
	Graph *ng;
	string gt("dimacs");
	Builder *b = f.create_builder(gt);

    DEBUG("starting plane.dim graph\n");
    b->set_filename("../data/sh2-5.dim");
    ng = b->build_graph();

    for (int i = 0; i < ng->get_nnodes(); i++)
    {
        if (ng->is_foldable(i))
        {
            DEBUG("folding: %d\n", i);
            ng->fold_node(i);
        }
    }

    ng->print();
    ng->debug_data();
    LOG_CLOSE();
	return 0;
}
