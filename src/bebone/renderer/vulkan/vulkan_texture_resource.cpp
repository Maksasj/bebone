#include "vulkan_texture_resource.h"

namespace bebone::renderer {
    VulkanTextureResource::VulkanTextureResource(const std::string& name, const Vec2i& size, std::shared_ptr<VulkanDevice>& device) : ITextureResource(name) {
        textures = device->create_textures({static_cast<uint32_t>(size.x), static_cast<uint32_t>(size.y), 1}, VK_FORMAT_R32G32B32A32_SFLOAT, 3);
    }

    std::vector<std::shared_ptr<VulkanTexture>>& VulkanTextureResource::get_textures() {
        return textures;
    }
}
