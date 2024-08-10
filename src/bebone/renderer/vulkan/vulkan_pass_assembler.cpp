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

    std::shared_ptr<IUniformBuffer> VulkanPassAssembler::create_uniform_buffer(const size_t& size) {
        auto vulkan_program_manager = static_pointer_cast<VulkanProgramManager>(get_program_manager());
        auto pipeline_manager = static_pointer_cast<VulkanPipelineManager>(vulkan_program_manager->get_pipeline_manager());

        auto impl = std::make_shared<VulkanUniformBufferImpl>(device, pipeline_manager, size);
        return std::make_shared<IUniformBuffer>(impl);
    }

    std::shared_ptr<IRenderTarget> VulkanPassAssembler::create_present_target(const std::string& name) {
        return std::make_shared<IRenderTarget>(std::make_shared<VulkanRenderTargetImpl>(swap_chain), name);
    }

    std::shared_ptr<IRenderTarget> VulkanPassAssembler::create_render_target(
        const std::shared_ptr<IPassImpl>& pass_impl,
        const std::vector<std::shared_ptr<IAttachment>>& attachments,
        const Vec2i& viewport,
        const std::string& name
    ) {
        auto vulkan_pass = static_pointer_cast<VulkanPassImpl>(pass_impl)->get_vulkan_pass();

        return std::make_shared<IRenderTarget>(std::make_shared<VulkanRenderTargetImpl>(
            device,
            vulkan_pass,
            static_pointer_cast<VulkanTextureManager>(get_texture_manager()),
            attachments,
            viewport), name);
    }

    std::shared_ptr<VulkanDevice> VulkanPassAssembler::get_device() const {
        return device;
    }

    std::shared_ptr<VulkanSwapChain> VulkanPassAssembler::get_swap_chain() const {
        return swap_chain;
    }
}
