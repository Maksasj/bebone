#ifndef _BEBONE_RENDERER_IRENDER_GRAPH_H_
#define _BEBONE_RENDERER_IRENDER_GRAPH_H_

#include "renderer_backend.h"

#include "irender_pass.h"

namespace bebone::renderer {
    class IRenderGraph {
        private:
            std::vector<std::shared_ptr<IRenderPass>> render_passes;

        public:
            IRenderGraph();

            virtual void execute() = 0;
            virtual void reset() = 0;

            void append_pass(std::shared_ptr<IRenderPass>& render_pass);
            std::optional<std::shared_ptr<IRenderPass>> get_render_pass(const std::string& name) const;
    };
}

#endif
