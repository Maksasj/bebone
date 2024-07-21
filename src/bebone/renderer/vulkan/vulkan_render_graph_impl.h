#ifndef _BEBONE_RENDERER_VULKAN_RENDER_GRAPH_IMPL_H_
#define _BEBONE_RENDERER_VULKAN_RENDER_GRAPH_IMPL_H_

#include "../irenderer.h"
#include "../irender_graph_impl.h"
#include "vulkan_command_encoder.h"
#include "vulkan_pass_factory.h"
#include "vulkan_resource_factory.h"
#include "vulkan_pass_assembler.h"

namespace bebone::renderer {
    using namespace bebone::gfx;

    class VulkanRenderGraphImpl : public IRenderGraphImpl {
        private:
            std::shared_ptr<VulkanDevice> device;
            std::shared_ptr<VulkanSwapChain> swap_chain;
            std::vector<std::shared_ptr<VulkanCommandBuffer>> command_buffers;

            std::shared_ptr<VulkanProgramManager> program_manager;
            std::shared_ptr<VulkanTextureManager> texture_manager;

            uint32_t frame;

        public:
            VulkanRenderGraphImpl(
                const std::shared_ptr<VulkanDevice>& device,
                const std::shared_ptr<VulkanSwapChain>& swap_chain,
                const std::shared_ptr<VulkanProgramManager>& program_manager,
                const std::shared_ptr<VulkanTextureManager>& texture_manager);

            void assemble() override;
            void record() override;
            void submit() override;
            void reset() override;

            void resize_viewport(const Vec2i& new_size) override;

            std::shared_ptr<IPassFactory> create_pass_factory() const override;
            std::shared_ptr<IResourceFactory> create_resource_factory() const override;
    };
}

#endif