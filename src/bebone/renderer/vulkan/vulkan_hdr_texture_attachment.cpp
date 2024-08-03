#include "vulkan_hdr_texture_attachment.h"

namespace bebone::renderer {
    VulkanHDRTextureAttachment::VulkanHDRTextureAttachment(
        const std::string& name,
        const std::vector<TextureHandle>& handles
    ) : IHDRTextureAttachment(name), handles(handles) {

    }

    const std::vector<TextureHandle>& VulkanHDRTextureAttachment::get_handles() const {
        return handles;
    }
}
