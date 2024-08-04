#include "vulkan_texture.h"

namespace bebone::renderer {
    VulkanTexture::VulkanTexture(std::shared_ptr<VulkanTextureTuple> texture) : texture(texture) {

    }

    VulkanTexture::VulkanTexture(const std::string& file_path, std::shared_ptr<VulkanDevice>& device) {
        texture = device->create_texture(file_path);
    }

    std::shared_ptr<VulkanTextureTuple>& VulkanTexture::get_texture() {
        return texture;
    }

    TextureHandle VulkanTexture::get_handle() const {
        return static_cast<TextureHandle>(handle);
    }
}
