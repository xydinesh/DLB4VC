#include "Graph.h"
#include "log.h"
#include "gtest/gtest.h"

using namespace std;
using namespace dlb;

class DimacsFactoryTests: public testing::Test
{
public:
    Graph g;

	virtual void SetUp()
	{
		LOG_INIT("graph.log", "graph.log", 0);

        for (int i = 0; i < 5; i++)
            g.add_node();

        g.add_edge(0, 1);
        g.add_edge(0, 4);
        g.add_edge(1, 4);
        g.add_edge(1, 2);
        g.add_edge(2, 3);
        g.add_edge(3, 4);
	}

	virtual void TearDown()
	{
		LOG_CLOSE();
	}
};

TEST_F(DimacsFactoryTests, testGetNnodes)
{
	EXPECT_EQ(5, g.get_nnodes());
}
