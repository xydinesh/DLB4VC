#ifndef __DLB4VC_BUILDER_H__
#define __DLB4VC_BUILDER_H__
#include "Graph.h"

namespace dlb {

	class GraphBuilder
	{
	protected:
		const char *filename;

	public:
		GraphBuilder() {};
		GraphBuilder(char const *f) : filename(f) {};
		virtual ~GraphBuilder() {};
		virtual Graph* build_graph() = 0;
		virtual void set_filename(const char *f) { filename = f;};
	};
}
#endif //__DLB4VC_BUILDER_H__
