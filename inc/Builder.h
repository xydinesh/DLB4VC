#ifndef __DLB4VC_BUILDER_H__
#define __DLB4VC_BUILDER_H__

namespace dlb {

	class GraphBuilder
	{
		char const *filename;

	public:
		GraphBuilder(char const *filename);
		virtual ~GraphBuilder();
		virtual Graph* build_graph() = 0;
	};
}
#endif //__DLB4VC_BUILDER_H__