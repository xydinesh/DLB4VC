#include "BuilderFactory.h"
#include "DimacsGraphBuilder.h"

using namespace dlb;

GraphBuilderFactory::GraphBuilderFactory()
{
}

GraphBuilderFactory::~GraphBuilderFactory()
{
}

GraphBuilder* GraphBuilderFactory::create_builder(string& name)
{
	if (name.compare("DIMACS") == 0|| name.compare("dimacs") == 0 || name.compare("Dimacs") == 0)
	{
		return new DimacsGraphBuilder();
	}

	return NULL;
}