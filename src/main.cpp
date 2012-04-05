#include "Node.h"
#include "Graph.h"
#include "BuilderFactory.h"
#include <iostream>
#include <stdio.h>
#include "log.h"
using namespace std;
using namespace dlb;

int main(int argc, char **argv)
{
  char x[100];
  char xe[100];
  sprintf(x, "graph.log");
  sprintf(xe, "graph.log");

  if (argc < 3)
  {
      cerr << "usage : " << argv[0] << "filename " << "k " << endl;
      return 0;
  }

  // 1: debug , 5: critical
  LOG_INIT(x, xe, 1);
  BuilderFactory f;
  Graph *ng;
  string gt("dimacs");
  Builder *b = f.create_builder(gt);
  DEBUG("starting plane.dim graph\n");
  b->set_filename(argv[1]);
  ng = b->build_graph();
  ng->print();
  if (ng->vertex_cover(atoi(argv[2])))
  {
      cout << "found valid vertex cover" << endl;
  }
  else
  {
      cout << "No vertex cover of size: "<< atoi(argv[2]) << endl;
  }

  LOG_CLOSE();
  return 0;
}
