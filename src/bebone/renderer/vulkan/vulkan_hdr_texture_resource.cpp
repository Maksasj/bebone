#include "vulkan_hdr_texture_resource.h"

namespace bebone::renderer {
    VulkanHDRTextureResource::VulkanHDRTextureResource(const std::string& name, const Vec2i& size, std::shared_ptr<VulkanDevice>& device) : IHDRTextureResource(name) {
        auto extent = VkExtent3D {static_cast<uint32_t>(size.x), static_cast<uint32_t>(size.y), 1};

        textures = device->create_textures(extent, VK_FORMAT_R32G32B32A32_SFLOAT, 3);
    }

    // VK_FORMAT_R8G8B8A8_UNORM

    std::vector<std::shared_ptr<VulkanTexture>>& VulkanHDRTextureResource::get_textures() {
        return textures;
    }
}
