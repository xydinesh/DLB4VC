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
  b->set_filename("../data/plane.dim");
  ng = b->build_graph();
  ng->print();
  LOG_CLOSE();
  return 0;
}
