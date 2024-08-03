#include "vulkan_depth_attachment.h"

namespace bebone::renderer {
    VulkanDepthAttachment::VulkanDepthAttachment(
        const std::string& name,
        const std::vector<TextureHandle>& handles
    ) : IDepthAttachment(name), handles(handles) {

    }

    const std::vector<TextureHandle>& VulkanDepthAttachment::get_handles() const {
        return handles;
    }
}
