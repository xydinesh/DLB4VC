#include "Graph.h"
#include <stdlib.h>
#include <iostream>
#include <climits>

#include "log.h"

using namespace dlb;
using namespace std;

Graph::Graph(void)
{
	this->nnodes = 0;
	this->nedges = 0;
    this->capacity = 0;
    this->next_label = 0;
    this->fold_nodes.clear();
    this->minsize = INT_MAX;
}


Graph::~Graph(void)
{
}

int Graph::add_node()
{
	Node n;
	this->nodes.push_back(n);
	this->degree.push_back(0);
    this->capacity++;
    this->next_label++;
	return this->nnodes++;
}

void Graph::delete_node(int u)
{
    // we check against graph capacity as it will not reduce when
    // delete nodes where as nnodes will reduce with active number of
    // nodes. 

	if (this->capacity < u)
	{
		cerr << "there is no node in " << u << endl;
		return;
	}

	const list<int> *nbrs = this->nodes[u].get_nbrs();

    while (!nbrs->empty())
	{
        edge_stack.push_front(make_pair(nbrs->front(), u));
        //DEBUG("%d:%d\n", nbrs->front(), u);
        this->delete_edge(nbrs->front(), u);
	}

	this->nodes[u].remove();
	this->degree[u] = 0;

	return;
}

void Graph::delete_edge(int u, int v)
{
	if (this->capacity < u)
	{
		cerr << "there is no node in " << u << endl;
		return;
	}

	if (this->capacity < v)
	{
        cerr << "there is no node in " << v << endl;
		return;
	}

	if (u != v)
	{
		this->nodes[u].delete_nbr(v);
		this->nodes[v].delete_nbr(u);

		this->degree[u]--;
		this->degree[v]--;

		this->nedges--;
	}
}

void Graph::add_edge(int u, int v)
{
	if (this->capacity < u)
	{
		cerr << "there is no node in " << u << endl;
		return;
	}

	if (this->capacity < v)
	{
		cerr << "there is no node in " << v << endl;
		return;
	}

	if (u != v)
	{
		this->nodes[u].add_nbr(v);
		this->nodes[v].add_nbr(u);

		this->degree[u]++;
		this->degree[v]++;

		this->nedges ++;
	}
}

Node* Graph::get_node(int u)
{
	if (this->capacity < u)
	{
		cerr << "there is no node in " << u << endl;
		return NULL;
	}
	return &this->nodes[u];
}

int Graph::get_degree(int u)
{
	if (this->capacity < u)
	{
		cerr << "there is no node in " << u << endl;
		return -1;
	}

	return this->degree[u];
}

int Graph::get_nnodes()
{
	return this->nnodes;
}

int Graph::get_nedges()
{
	return this->nedges;
}

void Graph::print()
{
	for (int i = 0; i < this->capacity; i++)
	{
        cout << i << ":" << this->degree[i] << ":";
        this->nodes[i].print();	
	}
}

bool Graph::is_edge(int u, int v)
{
	if (this->capacity < u)
	{
		cerr << "there is no node in " << u << endl;
		return false;
	}

	if (this->capacity < v)
	{
		cerr << "there is no node in " << v << endl;
		return false;
	}

    if (u == v)
        return false;

    Node *n = this->get_node(u);
    if (n->get_size() > 0)
    {
        const list<int> *nbrs = n->get_nbrs();
        list<int>::const_iterator it = nbrs->begin();
        for (int j = 0; it != nbrs->end() && (j < this->degree[u]); ++it, j++)
            if (*it == v) return true;
    }
    return false;
}

int Graph::fold_node(int u)
{
    Node *n = this->get_node(u);
    Node nn;

    list<int> newlist;
    const list<int> *nlist = n->get_nbrs();

    DEBUG("node: %d:%d\n", u, this->next_label);
    fold_nodes[this->next_label].push_back(u);

    while(!nlist->empty())
    {
        int ni = nlist->front();
        fold_nodes[this->next_label].push_back(ni);
        
        // Get nbrs of the current node(u)'s nbrs
        // and add them to a newlist in order to create a new node.
        const list<int> *nnlist = this->get_node(ni)->get_nbrs();
        list<int>::const_iterator it = nnlist->begin();
        for (; it != nnlist->end(); ++it)
            newlist.push_back(*it);
        
        // deleted edges added into edge_stack
        this->delete_node(ni);
    }

    // Here we increase the capacity of the graph.
    this->nodes.push_back(nn);
    this->degree.push_back(nn.get_size());
    this->capacity++;

    newlist.remove(u);
    newlist.sort();
    newlist.unique();
    list<int>::iterator uit = newlist.begin();
    for (; uit != newlist.end(); ++uit)
    {
        GEN("%d ", *uit);
        this->add_edge(this->next_label, *uit);
    }
    GEN("\n");
    
    return this->next_label++;
}

bool Graph::is_foldable(int u)
{
    // In order to be foldable , a node has to have degree two and no
    // edge between nbrs.

    if (this->degree[u] != 2)
        return false;

    int a, b;
    const list<int> *nlist = this->get_node(u)->get_nbrs();
    list<int>::const_iterator it = nlist->begin();
    a = *(it++);
    b = *(it++);

    return !this->is_edge(a, b);
}

void Graph::debug_data()
{
    //print fold map
    //print edge map
    //print fold_nodes
    GEN("############### Fold Node Information ##################\n");
    for (int i = 0; i < this->capacity; i++)
    {
        if (fold_nodes.count(i) > 0)
        {
            list<int>::iterator it = fold_nodes[i].begin();
            DEBUG("%d: ", i);
            for (; it != fold_nodes[i].end(); ++it)
                GEN(" %d ", *it);
            GEN("\n");
        }
    }

    GEN("############### Edge Information ##################\n");
    list< pair<int,int> >::iterator pit = edge_stack.begin();
    for (; pit != edge_stack.end(); ++pit)
        GEN("%d:%d\n", (*pit).first, (*pit).second);
}

int Graph::get_vertex()
{
    int max = 0;
    int index = -1;

    for (int i = 0; i < this->capacity; i++)
    {
        if (this->degree[i] > max)
        {
            max = this->degree[i];
            index = i;
        }
    }

    return index;
}

int Graph::vertex_cover()
{
    int u = this->get_vertex();
    int stack_size = this->edge_stack.size();

    if (u < 0)
    {
        if (vc.size() < minsize)
        {
            minvc = vc;
            minsize = vc.size();
            DEBUG("current min vc: %d\n", minsize);
            list<int>::iterator it = vc.begin();
            GEN("vc: ");
            for (; it != vc.end(); ++it)
                GEN(" %d ", *it);
            GEN("\n");
        }
        return 0;
    }

    //DEBUG("u: %d:%d\n", u, stack_size);
    vc.push_back(u);
    this->delete_node(u);

    this->vertex_cover();

    int current_stack_size = this->edge_stack.size();
    while (current_stack_size > stack_size)
    {
        pair<int,int> element = this->edge_stack.front();
        this->add_edge(element.first, element.second);
        this->edge_stack.pop_front();
        current_stack_size --;
    }

    vc.remove(u);

    const list<int> *nbrs = this->get_node(u)->get_nbrs();
    while(!nbrs->empty())
    {
        vc.push_back(nbrs->front());
        this->delete_node(nbrs->front());
    }

    this->vertex_cover();

    current_stack_size = this->edge_stack.size();
    while (current_stack_size > stack_size)
    {
        pair<int,int> element = this->edge_stack.front();
        this->add_edge(element.first, element.second);
        this->edge_stack.pop_front();
        current_stack_size --;
    }

    nbrs = this->get_node(u)->get_nbrs();
    list<int>::const_iterator it = nbrs->begin();
    for (; it != nbrs->end(); ++it)
        vc.remove(*it);

    return 0;
}


bool Graph::verify()
{
    list<int>::iterator it = minvc.begin();
    GEN("vc: ");
    for (; it != minvc.end(); ++it)
    {
        GEN("%d ", *it);
        this->delete_node(*it);
    }
    GEN("\n");

    for (int i = 0; i < this->capacity; i++)
    {
        if (this->degree[i] > 0)
        {
            DEBUG("invalid vertex cover, edges availabe in: %d\n", i);
            return false;
        }
    }

    DEBUG("valid vertex cover\n");
    return true;
}

