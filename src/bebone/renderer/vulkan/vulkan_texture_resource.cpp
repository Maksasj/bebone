#include "vulkan_texture_resource.h"

namespace bebone::renderer {
    VulkanTextureResource::VulkanTextureResource(
        const std::string& name,
        const std::vector<std::shared_ptr<VulkanTexture>>& textures
    ) : ITextureResource(name), textures(textures) {
        handles.reserve(textures.size());

        for(auto& texture : textures)
            handles.push_back(texture->get_handle());
    }

    std::vector<std::shared_ptr<VulkanTexture>>& VulkanTextureResource::get_textures() {
        return textures;
    }
}
