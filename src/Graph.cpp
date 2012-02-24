#include "Graph.h"
#include <stdlib.h>
#include <iostream>
#include "log.h"

using namespace dlb;
using namespace std;

Graph::Graph(void)
{
	this->nnodes = 0;
	this->nedges = 0;
    this->capacity = 0;
    this->next_label = 0;
    this->fold_map.clear();
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
    // we check agains graph capacity as it will not reduce when
    // delete nodes where as nnodes will reduce with active number of
    // nodes. 

	if (this->capacity < u)
	{
		cerr << "there is no node in " << u << endl;
		return;
	}

	const list<int> *nbrs = this->nodes[u].get_nbrs();
	list<int>::const_iterator it = nbrs->begin();

	int j = 0;

	for (; it != nbrs->end() && (j < this->degree[u]); ++it, j++)
	{
		this->nodes[*it].delete_nbr(u);
		this->degree[*it]--;
		this->nedges --;
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
    vector<int> nlist_vec(nlist->begin(), nlist->end());
    int ns = nlist->size();

    DEBUG("node: %d:%d\n", u, this->next_label);
    fold_map[u] = this->next_label;
    
    for (int i = 0; i < ns; i++)
    {
        fold_map[nlist_vec[i]] = this->next_label;
        const list<int> *nnlist = this->get_node(nlist_vec[i])->get_nbrs();
        list<int>::const_iterator it = nnlist->begin();
        for (; it != nnlist->end(); ++it)
        {
            newlist.push_back(*it);
            edge_map[nlist_vec[i]].push_back(*it);
        }
        
        this->delete_node(nlist_vec[i]);
    }

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
    GEN("############### Fold Information ##################\n");
    for (int i = 0; i < this->capacity; i++)
    {
        if (fold_map.count(i) > 0)
        {
            DEBUG("%d:%d\n", i, fold_map[i]);
        }
    }

    GEN("############### Edge Information ##################\n");
    for (int i = 0; i < this->capacity; i++)
    {
        if (edge_map.count(i) > 0)
        {
            DEBUG("edges for %d:\n", i);
            list<int>::iterator it = edge_map[i].begin();
            for (; it != edge_map[i].end(); ++it)
            {
                GEN("%d ", *it);
            }
            GEN("\n");
        }
    }
}
