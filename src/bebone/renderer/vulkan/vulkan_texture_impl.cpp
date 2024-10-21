#include "vulkan_texture_impl.h"

namespace bebone::renderer {
    VulkanTextureImpl::VulkanTextureImpl(std::shared_ptr<VulkanTexture> texture) : texture(texture) {

    }

    VulkanTextureImpl::VulkanTextureImpl(const std::string& file_path, std::shared_ptr<VulkanDevice>& device) {
        texture = device->create_texture(file_path);
    }

    std::shared_ptr<VulkanTexture>& VulkanTextureImpl::get_texture() {
        return texture;
    }

    TextureHandle VulkanTextureImpl::get_handle() const {
        return static_cast<TextureHandle>(handle);
    }
}
