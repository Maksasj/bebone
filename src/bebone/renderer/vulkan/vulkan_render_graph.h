#ifndef _BEBONE_RENDERER_VULKAN_RENDER_GRAPH_H_
#define _BEBONE_RENDERER_VULKAN_RENDER_GRAPH_H_

#include "../irenderer.h"
#include "../irender_graph.h"
#include "vulkan_pass_factory.h"
#include "vulkan_command_encoder.h"

namespace bebone::renderer {
    using namespace bebone::gfx;

    class VulkanRenderGraph : public IRenderGraph {
        private:

        public:
            VulkanRenderGraph();

            void execute() override;
            void reset() override;

            std::shared_ptr<IPassFactory> create_pass_factory() const override;
    };
}

#endif
