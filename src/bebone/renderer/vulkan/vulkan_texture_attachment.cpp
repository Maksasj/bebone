#include "vulkan_texture_attachment.h"

namespace bebone::renderer {
    VulkanTextureAttachment::VulkanTextureAttachment(
        const std::string& name,
        const std::vector<TextureHandle>& handles
    ) : ITextureAttachment(name), handles(handles) {

    }

    const std::vector<TextureHandle>& VulkanTextureAttachment::get_handles() const {
        return handles;
    }
}
