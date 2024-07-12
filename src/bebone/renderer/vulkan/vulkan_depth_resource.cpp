#include "vulkan_depth_resource.h"

namespace bebone::renderer {
    VulkanDepthResource::VulkanDepthResource(const std::string& name, const Vec2i& size, std::shared_ptr<VulkanDevice>& device) : IDepthResource(name) {
        depth_textures = device->create_depth_image_tuples({ static_cast<uint32_t>(size.x), static_cast<uint32_t>(size.y), 1 }, 3);
    }

    std::vector<std::shared_ptr<VulkanDepthImageTuple>>& VulkanDepthResource::get_textures() {
        return depth_textures;
    }
}
