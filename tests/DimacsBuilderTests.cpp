#include "Graph.h"
#include "log.h"
#include "Builder.h"
#include "BuilderFactory.h"
#include "gtest/gtest.h"

using namespace std;
using namespace dlb;

class DimacsBuilderTests: public testing::Test
{
public:
    Graph *g;
    Builder *b;
    BuilderFactory bf;

	virtual void SetUp()
	{
		LOG_INIT("graph.log", "graph.log", 0);
        DEBUG("create graph data/plane.dim\n");
        string s("dimacs");
        b = bf.create_builder(s);
        b->set_filename("../data/plane.dim");
        g = b->build_graph();
	}

	virtual void TearDown()
	{
        delete b;
		LOG_CLOSE();
	}
};

TEST_F(DimacsBuilderTests, testGetNnodes)
{
    g->print();
	EXPECT_EQ(13, g->get_nnodes());
}
