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
    this->ocapacity = 0;
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
    this->ocapacity++;
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
    int vc_size = this->vc.size();
    int next_label = this->next_label;
    int capacity = this->capacity;
    int ufsize = 0;

    if (u < 0)
    {
        ufsize = this->unfold_vertex_cover();
        if (ufsize < minsize)
        {
            DEBUG("fn size:%d\n", fold_nodes.size());
            minvc = unfold_vc;
            minsize = ufsize;
            DEBUG("current min vc: %d\n", minsize);
            list<int>::iterator it = unfold_vc.begin();
            GEN("vc: ");
            for (; it != unfold_vc.end(); ++it)
                GEN(" %d ", *it);
            GEN("\n");
        }
        return 0;
    }

    DEBUG("u: %d:%d\n", u, stack_size);
    vc.push_back(u);
    this->delete_node(u);

    // 1 - degree rule
    //this->one_degree();
    this->two_degree();
    this->one_degree();

    this->vertex_cover();

    int current_stack_size = this->edge_stack.size();
    while (current_stack_size > stack_size)
    {
        pair<int,int> element = this->edge_stack.front();
        if (element.first < next_label && element.second < next_label)
            this->add_edge(element.first, element.second);
        this->edge_stack.pop_front();
        current_stack_size --;
    }

    int current_vc_size = this->vc.size();
    while (current_vc_size > vc_size)
    {
        vc.pop_back();
        current_vc_size --;
    }

    // restoring capacity and next labels
    this->capacity = capacity;
    this->next_label = next_label;
    this->degree.resize(capacity);
    this->nodes.resize(capacity);

    const list<int> *nbrs = this->get_node(u)->get_nbrs();
    while(!nbrs->empty())
    {
        vc.push_back(nbrs->front());
        this->delete_node(nbrs->front());
    }

    // 1 - degree rule
    //this->one_degree();
    this->two_degree();
    this->one_degree();

    this->vertex_cover();

    current_stack_size = this->edge_stack.size();
    while (current_stack_size > stack_size)
    {
        pair<int,int> element = this->edge_stack.front();
        if (element.first < next_label && element.second < next_label)
            this->add_edge(element.first, element.second);
        this->edge_stack.pop_front();
        current_stack_size --;
    }

    current_vc_size = this->vc.size();
    while (current_vc_size > vc_size)
    {
        vc.pop_back();
        current_vc_size --;
    }

    // restoring capacity and next labels
    this->capacity = capacity;
    this->next_label = next_label;
    this->degree.resize(capacity);
    this->nodes.resize(capacity);


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


void Graph::one_degree()
{
    for (int i = 0; i < this->capacity; i++)
    {
        if (this->degree[i] == 1)
        {
            int nbr = this->get_node(i)->get_nbrs()->front();
            vc.push_back(nbr);
            this->delete_node(nbr);
        }
    }
}

void Graph::two_degree()
{
    for (int i = 0; i < this->capacity; i++)
    {
        if (this->degree[i] == 2)
        {
            GEN("%d:%d", i, this->degree[i]);
            if (this->is_foldable(i))
            {
                DEBUG("folding : %d\n", i);
                this->fold_node(i);   
            }
            else
            {
                DEBUG("two: %d\n", i);
                const list<int> *nbrs = this->get_node(i)->get_nbrs();
                int nbr = 0;
                while(!nbrs->empty())
                {
                    nbr = nbrs->front();
                    vc.push_back(nbr);
                    this->delete_node(nbr);
                }
            }
        }
    }
}


int Graph::unfold_vertex_cover()
{
    int fsz = fold_nodes.size();
    if (fsz == 0)
    {
        unfold_vc = vc;
        return vc.size();
    }
    DEBUG("ocapacity: %d\n", this->ocapacity);
    DEBUG("unfolding\n");
    list<int>::iterator vc_it = vc.begin();
    uf_touch.clear();
    unfold_vc.clear();

    for (; vc_it != vc.end(); ++vc_it)
    {
        DEBUG("vc: %d\n", *vc_it);
        // check for normal/unfolded nodes
        if (this->ocapacity > *vc_it)
            unfold_vc.push_back(*vc_it);
        else
        {
            uf_touch[*vc_it] = 1;
            vector<int> fn;
            int fnz;

            DEBUG("uf:%d\n", *vc_it);            
            this->unfold_vertex(*vc_it, true, fn);
            fnz = fn.size();
            
            for (int i = 0; i < fnz; i++)
            {
                DEBUG("fnz: %d\n", fn[i]);
                unfold_vc.push_back(fn[i]);
            }
        }
    }

    map<int, list<int> >::reverse_iterator fn_it = fold_nodes.rbegin();
    for (; fn_it != fold_nodes.rend(); ++fn_it)
    {
        // check whether it is already unfolded
        if (!uf_touch.count((*fn_it).first) > 0)
        {
            DEBUG("notvc:%d\n", (*fn_it).first);
            vector<int> fn;
            int fnz;

            this->unfold_vertex((*fn_it).first, false, fn);
            fnz = fn.size();
            
            for (int i = 0; i < fnz; i++)
            {
                DEBUG("fnz: %d\n", fn[i]);
                unfold_vc.push_back(fn[i]);
            }
        }

    }
    unfold_vc.sort();
    unfold_vc.unique();
    return unfold_vc.size();
}

void Graph::unfold_vertex(int u, bool in, vector<int> &n)
{
    if (this->ocapacity > u)
    {
        if (in)
            n.push_back(u);
        
        return;
    }

    list<int>::iterator it = this->fold_nodes[u].begin();
    vector<int> ut;
    vector<int> uf;

    this->uf_touch[u] = 1;
    
    uf.push_back(*it++);
    ut.push_back(*it++);
    ut.push_back(*it++);
    
    this->unfold_vertex(uf[0], !in, n);
    this->unfold_vertex(ut[0], in, n);
    this->unfold_vertex(ut[1], in, n);
    
    return;
}
