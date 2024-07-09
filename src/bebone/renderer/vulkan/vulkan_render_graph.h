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
            std::shared_ptr<VulkanDevice> device;
            std::shared_ptr<VulkanSwapChain> swap_chain;

            std::shared_ptr<VulkanPipelineManager> pipeline_manager;
            std::vector<std::shared_ptr<VulkanCommandBuffer>> command_buffers;

            uint32_t frame;

        public:
            VulkanRenderGraph(
                const std::shared_ptr<VulkanDevice>& device,
                const std::shared_ptr<VulkanSwapChain>& swap_chain);

            void record() override;
            void submit() override;
            void reset() override;

            std::shared_ptr<IPassFactory> create_pass_factory() const override;
    };
}

#endif
