#include "vulkan_render_target.h"

namespace bebone::renderer {
    using namespace bebone::gfx;

    VulkanRendererTarget::VulkanRendererTarget(
        const std::vector<std::shared_ptr<IAttachment>>& attachments,
        const Vec2i& viewport
    ) {
        for(size_t i = 0; i < 3; ++i) { // Todo, fif
            auto vulkan_attachments = std::vector<std::shared_ptr<VulkanImageView>> {};
            vulkan_attachments.reserve(attachments.size());

            for(auto& attachment : attachments)
                vulkan_attachments.push_back(static_pointer_cast<VulkanTextureImpl>(texture_manager->get_texture(attachment[i]).value())->get_texture()->view);

            framebuffers.push_back(device->create_framebuffer(vulkan_attachments, render_pass, viewport));
        }
    }
}
