#include "vulkan_texture.h"

namespace bebone::renderer {
    VulkanTexture::VulkanTexture(const std::string& file_path, std::shared_ptr<gfx::VulkanDevice>& device) {
        texture = device->create_texture(file_path);
    }

    std::shared_ptr<gfx::VulkanTexture>& VulkanTexture::get_texture() {
        return texture;
    }
}
