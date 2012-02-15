#ifndef __DLB4VC_NODE_H__
#define	__DLB4VC_NODE_H__
#include<list>
using namespace std;

namespace dlb {

	class Node {
	private:
		list<int> nbrs;
		int size;
	public:
		Node();
		~Node();
		list<int>* get_nbrs();
		int get_size() const;
		void add_nbr(int i);
		void delete_nbr(int i);
		void remove();
		void print();
	};

}
#endif // __DLB4VC_NODE_H__