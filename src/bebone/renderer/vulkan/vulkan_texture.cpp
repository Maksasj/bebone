#include "vulkan_texture.h"

namespace bebone::renderer {
    VulkanTexture::VulkanTexture(const std::string& file_path, std::shared_ptr<VulkanDevice>& device) {
        texture = device->create_texture(file_path);
    }

    std::shared_ptr<VulkanTextureTuple>& VulkanTexture::get_texture() {
        return texture;
    }

    const VulkanBindlessTextureHandle& VulkanTexture::get_handle() const {
        return handle;
    }
}
