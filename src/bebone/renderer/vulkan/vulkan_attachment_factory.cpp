#include "vulkan_attachment_factory.h"

namespace bebone::renderer {
    VulkanAttachmentFactory::VulkanAttachmentFactory(
        const std::shared_ptr<ITextureManager>& texture_manager
    ) : texture_manager(texture_manager) {

    }

    std::shared_ptr<IAttachment> VulkanAttachmentFactory::create_texture_attachment(const std::string& name, const Vec2i& size) {
        auto impl = std::make_shared<VulkanAttachmentImpl>(texture_manager, size, Color);
        return std::make_shared<IAttachment>(impl, name);
    }

    std::shared_ptr<IAttachment> VulkanAttachmentFactory::create_hdr_texture_attachment(const std::string& name, const Vec2i& size) {
        auto impl = std::make_shared<VulkanAttachmentImpl>(texture_manager, size, HDRColor);
        return std::make_shared<IAttachment>(impl, name);
    }

    std::shared_ptr<IAttachment> VulkanAttachmentFactory::create_depth_attachment(const std::string& name, const Vec2i& size) {
        auto impl = std::make_shared<VulkanAttachmentImpl>(texture_manager, size, Depth);
        return std::make_shared<IAttachment>(impl, name);
    }
}
