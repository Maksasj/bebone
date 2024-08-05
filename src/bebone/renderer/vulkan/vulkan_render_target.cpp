#include "vulkan_render_target.h"

namespace bebone::renderer {
    using namespace bebone::gfx;

    VulkanRenderTarget::VulkanRenderTarget(const std::shared_ptr<VulkanSwapChain>& swap_chain) {
        framebuffers = swap_chain->render_target->framebuffers;
    }

    VulkanRenderTarget::VulkanRenderTarget(
        const std::shared_ptr<VulkanDevice>& device,
        const std::shared_ptr<gfx::VulkanRenderPass>& render_pass,
        const std::shared_ptr<VulkanTextureManager>& texture_manager,
        const std::vector<std::shared_ptr<IAttachment>>& attachments,
        const Vec2i& viewport
    ) {
        const auto extent = VkExtent2D { static_cast<uint32_t>(viewport.x), static_cast<uint32_t>(viewport.y) };

        for(size_t i = 0; i < 3; ++i) { // Todo, fif
            auto vulkan_attachments = std::vector<std::shared_ptr<VulkanImageView>> {};
            vulkan_attachments.reserve(attachments.size());

            for(auto& attachment : attachments) {
                auto handles = static_pointer_cast<VulkanAttachmentImpl>(attachment->get_impl())->get_handles();
                vulkan_attachments.push_back(static_pointer_cast<VulkanTextureImpl>(texture_manager->get_texture(handles[i]).value())->get_texture()->view);
            }

            framebuffers.push_back(device->create_framebuffer(vulkan_attachments, render_pass, extent));
        }
    }

    const std::vector<std::shared_ptr<VulkanFramebuffer>>& VulkanRenderTarget::get_framebuffers() {
        return framebuffers;
    }
}
