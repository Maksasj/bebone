#include "vulkan_depth_resource.h"

namespace bebone::renderer {
    VulkanDepthResource::VulkanDepthResource(const std::string& name, std::shared_ptr<VulkanDevice>& device) : IDepthResource(name) {
        depth_textures = device->create_depth_image_tuples({ 800, 600, 1 }, 3);
    }
}
