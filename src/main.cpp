#include "Node.h"
#include <iostream>

using namespace std;
using namespace dlb;

int main()
{
	cout << "dinesh" << endl;

	Node n;
	
	n.add_nbr(3);
	n.add_nbr(5);
	n.add_nbr(10);
	n.print();
	list<int> &nlist = n.get_nbrs();
	n.delete_nbr(3);
	n.delete_nbr(5);
	n.print();
	return 0;
}