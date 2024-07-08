#ifndef _BEBONE_RENDERER_VULKAN_RENDER_GRAPH_H_
#define _BEBONE_RENDERER_VULKAN_RENDER_GRAPH_H_

#include "../irenderer.h"

#include "../irender_graph.h"

#include "vulkan_command_encoder.h"

namespace bebone::renderer {
        using namespace bebone::gfx;

        class VulkanRenderGraph : public IRenderGraph {
            private:

            public:
                void execute() override;
        };
}

#endif
