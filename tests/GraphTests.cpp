#include "Graph.h"
#include "log.h"
#include "Builder.h"
#include "BuilderFactory.h"
#include "gtest/gtest.h"

using namespace std;
using namespace dlb;

class GraphTests: public testing::Test
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

TEST_F(GraphTests, testGetNnodes)
{
  EXPECT_EQ(5, g.get_nnodes());
}

TEST_F(GraphTests, testGetNEdges)
{
  EXPECT_EQ(6, g.get_nedges());
}

TEST_F(GraphTests, testAddEdge)
{
  g.add_edge(2, 4);
  EXPECT_EQ(7, g.get_nedges());
}

TEST_F(GraphTests, testNEdges)
{
  g.delete_node(3);
  EXPECT_EQ(4, g.get_nedges());
}

TEST_F(GraphTests, testDeleteEdge)
{
  g.delete_edge(0, 4);
  g.delete_edge(2, 3);
  EXPECT_EQ(4, g.get_nedges());
}

TEST_F(GraphTests, testGetDegree)
{
  EXPECT_EQ(2, g.get_degree(0));
  EXPECT_EQ(3, g.get_degree(1));
  g.delete_edge(0, 1);
  EXPECT_EQ(1, g.get_degree(0));
  EXPECT_EQ(3, g.get_degree(4));
  g.delete_node(3);
  EXPECT_EQ(0, g.get_degree(3));
  EXPECT_EQ(2, g.get_degree(4));
}


TEST_F(GraphTests, testIsEdge)
{
  EXPECT_EQ(6, g.get_nedges());
  EXPECT_TRUE(g.is_edge(3, 4));
  EXPECT_FALSE(g.is_edge(3, 1));
  g.add_edge(1, 3);
  EXPECT_TRUE(g.is_edge(3, 1));
  EXPECT_FALSE(g.is_edge(3, 3));
  EXPECT_FALSE(g.is_edge(3, -3));
  g.delete_node(3);
  EXPECT_FALSE(g.is_edge(3, 4));
}
