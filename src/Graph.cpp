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
  if (this->capacity < u)
    {
      cerr << "there is no node in " << u << endl;
      return;
    }

  const list<int> *nbrs = this->nodes[u].get_nbrs();
  list<int>::const_iterator it = nbrs->begin();

  // Remove u from nbrs
  for (; it != nbrs->end(); ++it)
    {
      this->nodes[*it].delete_nbr(u);
      this->degree[*it]--;
      this->nedges --;
    }

  // Now, remov u.
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

      this->nedges --;
    }


  return;
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


int Graph::select_vertex()
{
  int min = INT_MAX;
  int index = -1;

  for (int i = 0; i < this->capacity; i++)
    {
      if (this->degree[i] > 0)
        {
          if (this->degree[i] < min)
            {
              min = this->degree[i];
              index = i;
            }
        }
    }

  return index;
}

bool Graph::verify()
{
  for (int i = 0; i < this->capacity; i++)
    {
      if (this->degree[i] >  0)
        {
          cerr << "Vertex : " << i << " Degree : " << this->degree[i] << endl;
          return false;
        }
    }

  return true;
}

void Graph::restore(vector<int>& indegree)
{
  for (int i = 0; i < this->capacity; i++)
    {
      int diff = indegree[i] - this->degree[i];
      if (diff > 0)
        {
          this->nodes[i].undelete_nbrs(diff);
          this->degree[i] = indegree[i];
        }
    }

}

bool Graph::vertex_cover(int k1)
{
  int k = k1;

  if (k < 0)
    {
      return this->verify();
    }

  vector<int> indegree = this->degree;
  int u = this->select_vertex();
  int vcsize = this->vc.size();

  if (u < 0)
    {
      return this->verify();
    }

  const list<int> *nbrs = this->nodes[u].get_nbrs();
  list<int>::const_iterator it = nbrs->begin();

  for (; it != nbrs->end() && (k >= 0); ++it, k--)
    {
      vc.push_back(*it);
      this->delete_node(*it);
    }
  

  bool ret = this->vertex_cover(k);

  if (ret == true)
    return true;

  int vcdiff = this->vc.size() - vcsize;
  this->restore(indegree);
  k = k1;
  while (vcdiff >= 0)
    vc.pop_back();

  vc.push_back(u);
  k--;
  this->delete_node(u);

  return this->vertex_cover(k);
}


