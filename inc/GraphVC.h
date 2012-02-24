#ifndef __DLB4VC_GRAPHVC_H__
#define __DLB4VC_GRAPHVC_H__
#include "Node.h"
#include "Graph.h"

#include <vector>
#include <map>
#include <list>

using namespace std;
namespace dlb {
	class GraphVC : public Graph 
    {

      public:
		GraphVC();
		virtual ~GraphVC();
	};
}
#endif //__DLB4VC_GRAPHVC_H__
