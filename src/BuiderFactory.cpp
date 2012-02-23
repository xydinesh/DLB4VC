#include "BuilderFactory.h"
#include "DimacsBuilder.h"

using namespace dlb;

BuilderFactory::BuilderFactory()
{
}

BuilderFactory::~BuilderFactory()
{
}

Builder* BuilderFactory::create_builder(string& name)
{
	if (name.compare("DIMACS") == 0|| name.compare("dimacs") == 0 || name.compare("Dimacs") == 0)
	{
		return new DimacsBuilder();
	}

	return NULL;
}
