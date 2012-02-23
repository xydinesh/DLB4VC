#ifndef __DLB4VC_DIMACSBUILDER_H__
#define __DLB4VC_DIMACSBUILDER_H__
#include "Builder.h"
#include "Graph.h"
#include <string>

using namespace std;
namespace dlb {
class DimacsBuilder :
	public Builder
{
private:
	void split(const string &s, vector<int> &v);
public:
	DimacsBuilder(void);
	DimacsBuilder(const char *f);
	virtual ~DimacsBuilder(void);
	virtual Graph* build_graph();
};
}
#endif //__DLB4VC_DIMACSBUILDER_H__
