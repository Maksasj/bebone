#include "vulkan_attachment_factory.h"

namespace bebone::renderer {
    VulkanAttachmentFactory::VulkanAttachmentFactory(
        const std::shared_ptr<VulkanDevice>& device,
        const std::shared_ptr<VulkanTextureManager>& texture_manager
    ) : device(device), texture_manager(texture_manager) {

    }

    std::shared_ptr<ITextureAttachment> VulkanAttachmentFactory::create_texture_attachment(const std::string& attachment_name, const Vec2i& size) {
        auto handles = std::vector<TextureHandle> {};
        handles.reserve(3); // Todo, this is a FIF moment

        for(size_t i = 0; i < 3; ++i) // TODO, FIF, probably everything should be managed with handles
            handles.push_back(texture_manager->create_texture(size)); // Todo VK_FORMAT_R8G8B8A8_UNORM

        return std::make_shared<VulkanTextureAttachment>(attachment_name, handles);
    }

    std::shared_ptr<IHDRTextureAttachment> VulkanAttachmentFactory::create_hdr_texture_attachment(const std::string& attachment_name, const Vec2i& size) {
        auto handles = std::vector<TextureHandle> {};
        handles.reserve(3); // Todo, this is a FIF moment

        for(size_t i = 0; i < 3; ++i) // TODO, FIF, probably everything should be managed with handles
            handles.push_back(texture_manager->create_texture(size));

        return std::make_shared<VulkanHDRTextureAttachment>(attachment_name, handles);
    }

    std::shared_ptr<IDepthAttachment> VulkanAttachmentFactory::create_depth_attachment(const std::string& attachment_name, const Vec2i& size) {
        auto handles = std::vector<TextureHandle> {};
        handles.reserve(3); // Todo, this is a FIF moment

        for(size_t i = 0; i < 3; ++i) // TODO, FIF, probably everything should be managed with handles
            handles.push_back(texture_manager->create_depth_texture(size));

        return std::make_shared<VulkanDepthAttachment>(attachment_name, handles);
    }
}
