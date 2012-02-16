#ifndef __DLB4VC_DIMACSGRAPHBUILDER_H__
#define __DLB4VC_DIMACSGRAPHBUILDER_H__
#include "Builder.h"
#include "Graph.h"

namespace dlb {
class DimacsGraphBuilder :
	public GraphBuilder
{
private:
	void split(const string &s, vector<int> &v);
public:
	DimacsGraphBuilder(void);
	DimacsGraphBuilder(const char *f);
	virtual ~DimacsGraphBuilder(void);
	virtual Graph* build_graph();
};
}
#endif //__DLB4VC_DIMACSGRAPHBUILDER_H__
