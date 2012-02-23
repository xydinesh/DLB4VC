#include "Node.h"
#include "log.h"
#include "gtest/gtest.h"

using namespace std;
using namespace dlb;

class NodeTests: public testing::Test
{
public:
    Node *n;
    int size;
	virtual void SetUp()
	{
		//SetUp is called before every test
		LOG_INIT("node.log", "node.log", 0);
        n = new Node();
        n->add_nbr(3);
        n->add_nbr(5);
        n->add_nbr(10);
        size = 3;
	}

	virtual void TearDown()
	{
		//TearDown is called before every test
        delete n;
		LOG_CLOSE();
	}
};

TEST_F(NodeTests, testGetSize)
{
	EXPECT_EQ(size, n->get_size());
}

TEST_F(NodeTests, testDeleteNbrs)
{
   //delete a nbr who is not exsist
    n->delete_nbr(4);
	EXPECT_EQ(size, n->get_size());
}

TEST_F(NodeTests, testDeleteNbrs_1)
{
    n->delete_nbr(3);
	EXPECT_EQ(size - 1, n->get_size());
}

TEST_F(NodeTests, testAddNbrs)
{
    n->add_nbr(100);
	EXPECT_EQ(size + 1, n->get_size());
}

TEST_F(NodeTests, testNodeRemove)
{
    n->remove();
	EXPECT_EQ(-1, n->get_size());
}

TEST_F(NodeTests, testGetNbrList)
{
    list<int> const * nlist = n->get_nbrs();
	EXPECT_EQ(size, nlist->size());
}


