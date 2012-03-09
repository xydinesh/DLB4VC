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

      private:
        list<pair<int,int>> edge_stack;
        
      public:
		GraphVC();
		virtual ~GraphVC();
        int vertex_cover();
	};
}
#endif //__DLB4VC_GRAPHVC_H__
