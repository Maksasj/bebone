#ifndef _BEBONE_RENDERER_VULKAN_PASS_ASSEMBLER_H_
#define _BEBONE_RENDERER_VULKAN_PASS_ASSEMBLER_H_

#include "renderer_backend.h"
#include "ipass_assembler.h"
#include "vulkan_render_target.h"

#include "vulkan_program_manager.h"
#include "vulkan_texture_manager.h"
#include "vulkan_mesh_manager.h"
#include "vulkan_uniform_buffer_impl.h"

namespace bebone::renderer {
    using namespace bebone::gfx;

    class VulkanPassAssembler : public IPassAssembler {
        private:
            std::shared_ptr<VulkanDevice> device;
            std::shared_ptr<VulkanSwapChain> swap_chain;

        public:
            VulkanPassAssembler(
                const std::shared_ptr<VulkanDevice>& device,
                const std::shared_ptr<VulkanSwapChain>& swap_chain,
                const std::shared_ptr<IProgramManager>& program_manager,
                const std::shared_ptr<ITextureManager>& texture_manager,
                const std::shared_ptr<IMeshManager>& mesh_manager,
                const std::shared_ptr<IMaterialManager>& material_manager);

            std::shared_ptr<IUniformBuffer> create_uniform_buffer(const size_t& size) override;
            std::shared_ptr<IRenderTarget> create_present_target() override;
            std::shared_ptr<IRenderTarget> create_render_target(
                const std::shared_ptr<IPassImpl>& pass_impl,
                const std::vector<std::shared_ptr<IAttachment>>& attachments,
                const Vec2i& viewport) override;

            std::shared_ptr<VulkanDevice> get_device() const;
            std::shared_ptr<VulkanSwapChain> get_swap_chain() const;
    };
}

#endif