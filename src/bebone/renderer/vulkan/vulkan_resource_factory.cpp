#include "vulkan_resource_factory.h"

namespace bebone::renderer {
    std::shared_ptr<ITextureResource> VulkanResourceFactory::create_texture_resource(const std::string& resource_name) {
        return std::make_shared<VulkanTextureResource>(resource_name);
    }
    std::shared_ptr<IDepthResource> VulkanResourceFactory::create_depth_resource(const std::string& resource_name) {
        return std::make_shared<VulkanDepthResource>(resource_name);
    }
}
