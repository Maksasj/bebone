#include "vulkan_texture_manager.h"

namespace bebone::renderer {
    VulkanTextureManager::VulkanTextureManager(
        const std::shared_ptr<VulkanDevice>& device,
        const std::shared_ptr<VulkanProgramManager>& program_manager
    ) : device(device), program_manager(program_manager) {

    }

    TextureHandle VulkanTextureManager::create_texture(const Vec2i& extent) {
        auto vulkan_extent = VkExtent3D { static_cast<uint32_t>(extent.x), static_cast<uint32_t>(extent.y), 1};

        auto vulkan_texture = device->create_texture(vulkan_extent, VK_FORMAT_R32G32B32A32_SFLOAT);
        auto texture = std::make_shared<VulkanTexture>(vulkan_texture);

        program_manager->bind_texture(texture);
        textures.push_back(texture);

        return static_cast<TextureHandle>(texture->get_handle());;
    }

    TextureHandle VulkanTextureManager::create_depth_texture(const Vec2i& extent) {
        auto vulkan_extent = VkExtent3D { static_cast<uint32_t>(extent.x), static_cast<uint32_t>(extent.y), 1};
        auto format = device->find_depth_format();

        auto [ image, memory ] = device->create_image_memory(format, vulkan_extent,
            { .usage = VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT | VK_IMAGE_USAGE_SAMPLED_BIT } // Todo VK_IMAGE_USAGE_SAMPLED_BIT
        );

        auto sampler = device->create_sampler();
        auto view = device->create_image_view(*image, format, {
            .subresource_range = { .aspect_mask = VK_IMAGE_ASPECT_DEPTH_BIT },
        });

        auto vulkan_texture = std::make_shared<VulkanTextureTuple>(image, memory, view, sampler);
        auto texture = std::make_shared<VulkanTexture>(vulkan_texture);

        program_manager->bind_texture(texture);
        textures.push_back(texture);

        return static_cast<TextureHandle>(texture->get_handle());
    }

    TextureHandle VulkanTextureManager::load_texture_from_file(const std::string& file_path) {
        auto texture = std::make_shared<VulkanTexture>(file_path, device);

        program_manager->bind_texture(texture);
        textures.push_back(texture);

        std::cout << static_cast<u32>(texture->get_handle()) << "\n";

        return static_cast<TextureHandle>(texture->get_handle());
    }

    std::optional<std::shared_ptr<ITexture>> VulkanTextureManager::get_texture(const TextureHandle& handle) const {
        for(auto& texture : textures)
            if(static_cast<TextureHandle>(texture->get_handle()) == handle)
                return texture;

        return std::nullopt;
    }
}
