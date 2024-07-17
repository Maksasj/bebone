#include "vulkan_texture_manager.h"

namespace bebone::renderer {
    VulkanTextureManager::VulkanTextureManager(
        const std::shared_ptr<VulkanDevice>& device,
        const std::shared_ptr<VulkanProgramManager>& program_manager
    ) : device(device), program_manager(program_manager) {

    }

    std::shared_ptr<ITexture> VulkanTextureManager::create_texture(const Vec2i& extent) {
        auto vulkan_extent = VkExtent3D {
            static_cast<uint32_t>(extent.x),
            static_cast<uint32_t>(extent.y),
            1};

        auto vulkan_texture = device->create_texture(vulkan_extent, VK_FORMAT_R32G32B32A32_SFLOAT);
        auto texture = std::make_shared<VulkanTexture>(vulkan_texture);

        program_manager->bind_texture(texture);

        return texture;
    }

    std::shared_ptr<ITexture> VulkanTextureManager::create_texture(const Vec2i& extent, VkFormat format) {
        auto vulkan_extent = VkExtent3D {
            static_cast<uint32_t>(extent.x),
            static_cast<uint32_t>(extent.y),
            1};

        auto vulkan_texture = device->create_texture(vulkan_extent, format);
        auto texture = std::make_shared<VulkanTexture>(vulkan_texture);

        program_manager->bind_texture(texture);

        return texture;
    }

    std::shared_ptr<ITexture> VulkanTextureManager::load_texture_from_file(const std::string& file_path) {
        auto texture = std::make_shared<VulkanTexture>(file_path, device);

        program_manager->bind_texture(texture);

        return texture;
    }
}
