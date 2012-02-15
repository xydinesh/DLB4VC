#ifndef __DLB4VC_BUILDER_H__
#define __DLB4VC_BUILDER_H__
#include "Graph.h"

namespace dlb {

	class GraphBuilder
	{
	protected:
		char const *filename;

	public:
		GraphBuilder() {};
		GraphBuilder(char const *f) : filename(f) {};
		virtual ~GraphBuilder() {};
		virtual Graph* build_graph() = 0;
	};
}
#endif //__DLB4VC_BUILDER_H__