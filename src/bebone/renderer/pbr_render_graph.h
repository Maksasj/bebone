#ifndef _BEBONE_RENDERER_PBR_RENDER_GRAPH_H_
#define _BEBONE_RENDERER_PBR_RENDER_GRAPH_H_

#include "irender_graph.h"

namespace bebone::renderer {
    using namespace bebone::gfx;

    class PBRRenderGraph : public IRenderGraph {
        protected:
            std::shared_ptr<IDeferredGPass> gpass;
            std::shared_ptr<IPresentPass> present;

        public:
            PBRRenderGraph(const std::string& name, const std::shared_ptr<IRenderGraphImpl>& impl);

            void submit_geometry(const std::shared_ptr<IMesh>& mesh, const Transform& transform) override;
            void submit_ui_geometry(const std::shared_ptr<IMesh>& mesh, const Transform& transform) override;
    };
}

#endif
