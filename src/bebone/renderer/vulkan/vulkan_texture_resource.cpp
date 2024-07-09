#include "vulkan_texture_resource.h"

namespace bebone::renderer {
    VulkanTextureResource::VulkanTextureResource(const std::string& name, std::shared_ptr<VulkanDevice>& device) : ITextureResource(name) {
        textures = device->create_textures({800, 600, 1}, VK_FORMAT_R32G32B32A32_SFLOAT, 3);
    }

    std::vector<std::shared_ptr<VulkanTexture>>& VulkanTextureResource::get_textures() {
        return textures;
    }
}
