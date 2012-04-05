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

  return;
}

void Graph::delete_edge(int u, int v)
{

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


