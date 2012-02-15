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

Graph* DimacsGraphBuilder::build_graph()
{
	ifstream infile(filename);
	stringstream ss;

	if (!infile)
	{
		cerr << "unable to open input file: " << filename << endl;
		return NULL;
	}

	string line;
	while(infile.good())
	{
		getline(infile, line);
		ss >> line;
		cout << ss.str();
	}
	

	return NULL;
}
