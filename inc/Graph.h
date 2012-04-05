#ifndef __DLB4VC_GRAPH_H__
#define __DLB4VC_GRAPH_H__
#include "Node.h"

#include <vector>
#include <list>

using namespace std;
namespace dlb {
  class Graph {
  protected:
    vector<Node> nodes;
    vector<int> degree;
    list<int> vc;

    int nnodes;
    int nedges;
    int capacity;

  public:
    Graph();
    virtual ~Graph();
    Node* get_node(int i);
    void add_edge(int u, int v);
    void delete_edge(int u, int v);
    void delete_node(int u);
    int add_node();
    int get_degree(int u);
    int get_nnodes();
    int get_nedges();
    bool is_edge(int u, int v);
    void print();
    bool vertex_cover(int k);
    bool verify();
    int select_vertex();
    void restore(vector<int>& indegree);
    void high_degree (int &k);
    void one_degree(int &k);
    void process_nodes(int& k);
  };
}
#endif //__DLB4VC_GRAPH_H__
