#ifndef __DLB4VC_BUILDER_FACTORY_H__
#define __DLB4VC_BUILDER_FACTORY_H__
#include "Builder.h"
#include <string>

namespace dlb {

	class BuilderFactory {
      public:
		BuilderFactory();
		virtual ~BuilderFactory();
		Builder* create_builder(string& name);
	};
}
#endif //__DLB4VC_BUILDER_FACTORY_H__
