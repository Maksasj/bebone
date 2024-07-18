#include "vulkan_depth_resource.h"

namespace bebone::renderer {
    VulkanDepthResource::VulkanDepthResource(
        const std::string& name,
        const std::vector<TextureHandle>& handles
    ) : IDepthResource(name), handles(handles) {

    }

    const std::vector<TextureHandle>& VulkanDepthResource::get_handles() const {
        return handles;
    }
}
