#include "vulkan_depth_resource.h"

namespace bebone::renderer {
    VulkanDepthResource::VulkanDepthResource(
        const std::string& name,
        const std::vector<std::shared_ptr<VulkanTexture>>& textures
    ) : IDepthResource(name), textures(textures) {
        handles.reserve(textures.size());

        for(auto& texture : textures)
            handles.push_back(texture->get_handle());
    }

    std::vector<std::shared_ptr<VulkanTexture>>& VulkanDepthResource::get_textures() {
        return textures;
    }
}
