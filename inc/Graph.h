#ifndef __DLB4VC_GRAPH_H__
#define __DLB4VC_GRAPH_H__
#include "Node.h"

#include <vector>

using namespace std;
namespace dlb {
	class Graph {
	private:
		vector<Node> nodes;
		vector<int> degree;
		int nnodes;
		int nedges;

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
	};
}
#endif //__DLB4VC_GRAPH_H__
