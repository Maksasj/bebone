#include "vulkan_texture_resource.h"

namespace bebone::renderer {
    VulkanTextureResource::VulkanTextureResource(
        const std::string& name,
        const std::vector<TextureHandle>& handles
    ) : ITextureResource(name), handles(handles) {

    }

    const std::vector<TextureHandle>& VulkanTextureResource::get_handles() const {
        return handles;
    }
}
