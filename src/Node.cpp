#include "Node.h"
#include <iostream>

using namespace dlb;
using namespace std;

Node::Node()
{
	this->size = 0;
}

Node::~Node()
{
}

void Node::add_nbr(int a) 
{
	this->nbrs.push_back(a);
	this->size++;
}

void Node::delete_nbr(int a)
{
	int bs, as = 0;

	if (this->size > 0)
	{
		bs = this->nbrs.size();
		this->nbrs.remove(a);
		as = this->nbrs.size();

		if (bs > as)
        {
            this->dnbrs.push_front(a);
			this->size--;
        }
	}
}

void Node::print()
{
	list<int>::iterator it = this->nbrs.begin();
	for (int i = 0; it != this->nbrs.end() && i < this->size; ++it, i++)
		cout << *it << " ";
	cout << endl;
}

list<int> const * const Node::get_nbrs()
{
	if (this->size > 0)
		return &nbrs;
	return NULL;
}

int Node::get_size() const 
{
	return this->size;
}

void Node::remove()
{
    while (!this->nbrs.empty())
        this->delete_nbr(this->nbrs.front());
	this->size = 0;
}


// Undelete last n deleted nbrs
void Node::undelete_nbrs(int n)
{
    int i = 0;
    while ((!this->dnbrs.empty()) && (i < n))
    {
        this->nbrs.push_front(this->dnbrs.front());
        this->dnbrs.pop_front();
        this->size ++;
        i++;
    }
}
