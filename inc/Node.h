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
	list<int>& get_nbrs() const;
	int get_size();
	void add_nbr(int i);
	void delete_nbr(int i);
};
}
#endif // __DLB4VC_NODE_H__