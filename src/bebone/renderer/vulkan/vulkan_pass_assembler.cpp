#include "vulkan_pass_assembler.h"

namespace bebone::renderer {
    VulkanPassAssembler::VulkanPassAssembler(
        const std::shared_ptr<VulkanDevice>& device,
        const std::shared_ptr<VulkanSwapChain>& swap_chain,
        const std::shared_ptr<IProgramManager>& program_manager,
        const std::shared_ptr<ITextureManager>& texture_manager,
        const std::shared_ptr<IMeshManager>& mesh_manager,
        const std::shared_ptr<IMaterialManager>& material_manager
    ) : IPassAssembler(program_manager, texture_manager, mesh_manager, material_manager), device(device), swap_chain(swap_chain) {

    }

    std::shared_ptr<IRenderTarget> VulkanPassAssembler::create_present_target() {
        return std::make_shared<VulkanRenderTarget>(swap_chain);;
    }

    std::shared_ptr<IRenderTarget> VulkanPassAssembler::create_render_target(const std::shared_ptr<IPassImpl>& pass_impl, const std::vector<std::shared_ptr<IAttachment>>& attachments, const Vec2i& viewport) {
        auto vulkan_pass = static_pointer_cast<VulkanPassImpl>(pass_impl)->get_vulkan_pass();

        return std::make_shared<VulkanRenderTarget>(
            device,
            vulkan_pass,
            static_pointer_cast<VulkanTextureManager>(get_texture_manager()),
            attachments,
            viewport);
    }

    std::shared_ptr<VulkanDevice> VulkanPassAssembler::get_device() const {
        return device;
    }

    std::shared_ptr<VulkanSwapChain> VulkanPassAssembler::get_swap_chain() const {
        return swap_chain;
    }
}
