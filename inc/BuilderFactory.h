#ifndef __DLB4VC_BUILDER_FACTORY_H__
#define __DLB4VC_BUILDER_FACTORY_H__
#include "Builder.h"

namespace dlb {

	class GraphBuilderFactory {
	public:
		GraphBuilderFactory();
		virtual ~GraphBuilderFactory();
		GraphBuilder* create_builder(string& name);
	};
}
#endif //__DLB4VC_BUILDER_FACTORY_H__