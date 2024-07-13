#include "vulkan_texture_resource.h"

namespace bebone::renderer {
    VulkanTextureResource::VulkanTextureResource(const std::string& name, const Vec2i& size, std::shared_ptr<VulkanDevice>& device) : ITextureResource(name) {
        auto extent = VkExtent3D {static_cast<uint32_t>(size.x), static_cast<uint32_t>(size.y), 1};

        textures = device->create_textures(extent, VK_FORMAT_R8G8B8A8_UNORM, 3);
    }

    std::vector<std::shared_ptr<VulkanTexture>>& VulkanTextureResource::get_textures() {
        return textures;
    }
}
