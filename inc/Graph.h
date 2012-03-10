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
        int ocapacity;
        int next_label;

        map<int, list<int> >fold_nodes;
        list< pair<int,int> > edge_stack;
        map<int, int> uf_touch;

        list<int> vc;
        list<int> unfold_vc;
        list<int> minvc;
        int minsize;

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

        int vertex_cover();
        int get_vertex();
        bool verify();
        void one_degree();
        void two_degree();
        int unfold_vertex_cover();
        void unfold_vertex(int u, bool in, vector<int> &n);
	};
}
#endif //__DLB4VC_GRAPH_H__
