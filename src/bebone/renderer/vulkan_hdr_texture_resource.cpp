#include "vulkan_hdr_texture_resource.h"

namespace bebone::renderer {
    VulkanHDRTextureResource::VulkanHDRTextureResource(
        const std::string& name,
        const std::vector<TextureHandle>& handles
    ) : IHDRTextureResource(name), handles(handles) {

    }

    const std::vector<TextureHandle>& VulkanHDRTextureResource::get_handles() const {
        return handles;
    }
}
