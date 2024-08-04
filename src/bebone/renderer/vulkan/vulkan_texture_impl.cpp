#include "vulkan_texture_impl.h"

namespace bebone::renderer {
    VulkanTextureImpl::VulkanTextureImpl(std::shared_ptr<VulkanTextureTuple> texture) : texture(texture) {

    }

    VulkanTextureImpl::VulkanTextureImpl(const std::string& file_path, std::shared_ptr<VulkanDevice>& device) {
        texture = device->create_texture(file_path);
    }

    std::shared_ptr<VulkanTextureTuple>& VulkanTextureImpl::get_texture() {
        return texture;
    }

    TextureHandle VulkanTextureImpl::get_handle() const {
        return static_cast<TextureHandle>(handle);
    }
}
