#include "Node.h"
#include "log.h"
#include "gtest/gtest.h"

using namespace std;
using namespace dlb;

class NodeTests: public testing::Test
{
public:
    Node *n;
	virtual void SetUp()
	{
		//SetUp is called before every test
		LOG_INIT("node.log", "node.log", 0);
        n = new Node();
	}

	virtual void TearDown()
	{
		//TearDown is called before every test
        delete n;
		LOG_CLOSE();
	}
};

TEST_F(NodeTests, testNumNodes)
{
	n->add_nbr(3);
	n->add_nbr(5);
	n->add_nbr(10);
	list<int> *nlist = n->get_nbrs();
	EXPECT_EQ(3, nlist->size());
}
