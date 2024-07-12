#ifndef _BEBONE_RENDERER_PBR_RENDER_GRAPH_H_
#define _BEBONE_RENDERER_PBR_RENDER_GRAPH_H_

#include "irender_graph.h"

namespace bebone::renderer {
    using namespace bebone::gfx;

    class PBRRenderGraph : public IRenderGraph {
        public:
            PBRRenderGraph(const std::string& name, const std::shared_ptr<IRenderGraphImpl>& impl);
    };
}

#endif
