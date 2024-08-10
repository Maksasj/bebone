#ifndef _BEBONE_RENDERER_VULKAN_RENDER_GRAPH_IMPL_H_
#define _BEBONE_RENDERER_VULKAN_RENDER_GRAPH_IMPL_H_

#include "irenderer.h"
#include "irender_graph_impl.h"
#include "vulkan_command_encoder.h"
#include "vulkan_pass_factory.h"
#include "vulkan_attachment_factory.h"
#include "vulkan_pass_assembler.h"

#include "vulkan_program_manager.h"
#include "vulkan_texture_manager.h"
#include "vulkan_mesh_manager.h"
#include "vulkan_material_manager.h"

namespace bebone::renderer {
    using namespace bebone::gfx;

    class VulkanRenderGraphImpl : public IRenderGraphImpl {
        private:
            std::shared_ptr<VulkanDevice> device;
            std::shared_ptr<VulkanSwapChain> swap_chain;

            std::shared_ptr<VulkanProgramManager> program_manager;
            std::shared_ptr<VulkanTextureManager> texture_manager;
            std::shared_ptr<VulkanMeshManager> mesh_manager;
            std::shared_ptr<VulkanMaterialManager> material_manager;

            uint32_t frame;

            std::vector<VulkanCommandEncoder> encoders;

        public:
            VulkanRenderGraphImpl(
                const std::shared_ptr<VulkanDevice>& device,
                const std::shared_ptr<VulkanSwapChain>& swap_chain,
                const std::shared_ptr<VulkanProgramManager>& program_manager,
                const std::shared_ptr<VulkanTextureManager>& texture_manager,
                const std::shared_ptr<VulkanMeshManager>& mesh_manager,
                const std::shared_ptr<VulkanMaterialManager>& material_manager);

            void assemble() override;
            void record() override;
            void submit() override;
            void reset() override;

            void resize_viewport(const Vec2i& new_size) override;

            std::shared_ptr<IPassAssembler> create_pass_assembler() const override;
            std::shared_ptr<IPassImplFactory> create_pass_factory() const override;
            std::shared_ptr<IAttachmentFactory> create_attachment_factory() const override;
    };
}

#endif
