#ifndef _BEBONE_RENDERER_IRENDER_GRAPH_H_
#define _BEBONE_RENDERER_IRENDER_GRAPH_H_

#include "renderer_backend.h"

#include "irender_pass.h"

namespace bebone::renderer {
    class IRenderGraph {
        private:

        public:
            virtual std::shared_ptr<IRenderPass> get_render_pass(const std::string& name) const;
    };
}

#endif
