#ifndef __DLB4VC_GRAPH_H__
#define __DLB4VC_GRAPH_H__
#include "Node.h"

#include <vector>
#include <map>
#include <list>

using namespace std;
namespace dlb {
	class Graph {
      protected:
		vector<Node> nodes;
		vector<int> degree;
		int nnodes;
		int nedges;
        int capacity;
        int next_label;
        map<int, int> fold_map;
        map<int, list<int> >edge_map;

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
		void print();
        bool is_edge(int u, int v);
        bool is_foldable(int u);
        int fold_node(int u);
        void debug_data();
	};
}
#endif //__DLB4VC_GRAPH_H__
