#include "vulkan_resource_factory.h"

namespace bebone::renderer {
    VulkanResourceFactory::VulkanResourceFactory(
        const std::shared_ptr<VulkanDevice>& device,
        const std::shared_ptr<VulkanTextureManager>& texture_manager
    ) : device(device), texture_manager(texture_manager) {

    }

    std::shared_ptr<ITextureResource> VulkanResourceFactory::create_texture_resource(const std::string& resource_name, const Vec2i& size) {
        auto textures = std::vector<std::shared_ptr<VulkanTexture>> {};
        textures.reserve(3); // Todo, this is a FIF moment

        for(size_t i = 0; i < 3; ++i) // TODO, FIF, probably everything should be managed with handles
            textures.push_back(static_pointer_cast<VulkanTexture>(texture_manager->create_texture(size, VK_FORMAT_R8G8B8A8_UNORM)));

        return std::make_shared<VulkanTextureResource>(resource_name, textures);
    }

    std::shared_ptr<IHDRTextureResource> VulkanResourceFactory::create_hdr_texture_resource(const std::string& resource_name, const Vec2i& size) {
        auto textures = std::vector<std::shared_ptr<VulkanTexture>> {};
        textures.reserve(3); // Todo, this is a FIF moment

        for(size_t i = 0; i < 3; ++i) // TODO, FIF, probably everything should be managed with handles
            textures.push_back(static_pointer_cast<VulkanTexture>(texture_manager->create_texture(size, VK_FORMAT_R32G32B32A32_SFLOAT)));

        return std::make_shared<VulkanHDRTextureResource>(resource_name, textures);
    }

    std::shared_ptr<IDepthResource> VulkanResourceFactory::create_depth_resource(const std::string& resource_name, const Vec2i& size) {
        auto textures = std::vector<std::shared_ptr<VulkanTexture>> {};
        textures.reserve(3); // Todo, this is a FIF moment

        for(size_t i = 0; i < 3; ++i) // TODO, FIF, probably everything should be managed with handles
            textures.push_back(static_pointer_cast<VulkanTexture>(texture_manager->create_texture(size, device->find_depth_format())));

        return std::make_shared<VulkanDepthResource>(resource_name, textures);
    }
}
