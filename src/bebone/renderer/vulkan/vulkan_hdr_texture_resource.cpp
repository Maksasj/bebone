#include "vulkan_hdr_texture_resource.h"

namespace bebone::renderer {
    VulkanHDRTextureResource::VulkanHDRTextureResource(
        const std::string& name,
        const std::vector<std::shared_ptr<VulkanTexture>>& textures
    ) : IHDRTextureResource(name), textures(textures) {
        handles.reserve(textures.size());

        for(auto& texture : textures)
            handles.push_back(texture->get_handle());
    }

    std::vector<std::shared_ptr<VulkanTexture>>& VulkanHDRTextureResource::get_textures() {
        return textures;
    }
}
