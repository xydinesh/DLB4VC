#include "DimacsGraphBuilder.h"
#include <iostream>
#include <fstream>
#include <sstream>

using namespace dlb;

DimacsGraphBuilder::DimacsGraphBuilder(void)
{
}

DimacsGraphBuilder::DimacsGraphBuilder(const char *f) : GraphBuilder(f)
{

}

DimacsGraphBuilder::~DimacsGraphBuilder(void)
{
}

void DimacsGraphBuilder::split(const string &s, vector<int> &v)
{
	string tmp;
	int n;

	for (int i = 0; i < (int)s.size(); )
	{
		tmp.clear();
		while(isdigit(s[i]))
		{
			tmp += s[i];
            i++;
		}

		stringstream ss(tmp);
		ss >> n;
		v.push_back(n);

		while(!isdigit(s[i])) i++;
	}
}

Graph* DimacsGraphBuilder::build_graph()
{
	ifstream infile(filename);
	stringstream ss;
	int nnodes = 0, nedges = 0;
	Graph *g = new Graph();

	if (!infile)
	{
		cerr << "unable to open input file: " << filename << endl;
		return NULL;
	}

	string line;
	vector<int> elem;
	// Getting nnodes and nedges line.
	if (infile.good())
	{
		getline(infile, line);
		split(line, elem);
		cout << elem.size() << endl;
		nnodes = elem[0];
		nedges = elem[1];
	}
	else
	{
		cerr << "error with input file: " << filename << endl;
		return NULL;
	}

	cout << nnodes << ":" << nedges << endl;
	if (!(nnodes > 0) || !(nedges > 0))
	{
		cerr << "wrong node or edge count : " << nnodes << ":" << nedges << endl;
		return NULL;
	}

	for (int i = 0; i < nnodes; i++)
		g->add_node();


	while(infile.good())
	{
		elem.clear();
		getline(infile, line);

		split(line, elem);

		if (elem.size() > 1)
			g->add_edge(elem[0], elem[1]);
	}


	return g;
}
