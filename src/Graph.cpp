#include "Graph.h"
#include <stdlib.h>
#include <iostream>

using namespace dlb;
using namespace std;

Graph::Graph(void)
{
	this->nnodes = 0;
	this->nedges = 0;
}


Graph::~Graph(void)
{
}

int Graph::add_node()
{
	Node n;
	this->nodes.push_back(n);
	this->degree.push_back(0);
	return this->nnodes++;
}

void Graph::delete_node(int u)
{
	if (this->nnodes < u)
	{
		fprintf(stderr, "there is no node in %d\n", u);
		return;
	}

	list<int> *nbrs = this->nodes[u].get_nbrs();
	list<int>::iterator it = nbrs->begin();

	int j = 0;

	for (; it != nbrs->end() && (j < this->degree[u]); ++it, j++)
	{
		this->nodes[*it].delete_nbr(u);
		this->degree[*it]--;
		this->nedges --;
	}

	this->nodes[u].remove();
	this->degree[u] = -1;

	return;
}

void Graph::delete_edge(int u, int v)
{
	if (this->nnodes < u)
	{
		fprintf(stderr, "there is no node in %d\n", u);
		return;
	}

	if (this->nnodes < v)
	{
		fprintf(stderr, "there is no node in %d\n", v);
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
	if (this->nnodes < u)
	{
		fprintf(stderr, "there is no node in %d\n", u);
		return;
	}

	if (this->nnodes < v)
	{
		fprintf(stderr, "there is no node in %d\n", v);
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
	if (this->nnodes < u)
	{
		fprintf(stderr, "there is no node in %d\n", u);
		return NULL;
	}
	return &this->nodes[u];
}

int Graph::get_degree(int u)
{
	if (this->nnodes < u)
	{
		fprintf(stderr, "there is no node in %d\n", u);
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
	for (int i = 0; i < this->nnodes; i++)
	{
		cout << i << ":" << this->degree[i] << ":";
		this->nodes[i].print();	
	}
}
