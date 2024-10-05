#include "vulkan_attachment_factory.h"

namespace bebone::renderer {
    VulkanAttachmentFactory::VulkanAttachmentFactory(
        const std::shared_ptr<ITextureManager>& texture_manager
    ) : texture_manager(texture_manager) {
        LOG_TRACE("Created Vulkan Attachment factory");
    }

    std::shared_ptr<IAttachment> VulkanAttachmentFactory::create_texture_attachment(const std::string& name, const Vec2i& size) {
        auto impl = std::make_shared<VulkanAttachmentImpl>(texture_manager, size, Color);

        LOG_INFORMATION("Created Vulkan texture attachment");
        return std::make_shared<IAttachment>(impl, name);
    }

    std::shared_ptr<IAttachment> VulkanAttachmentFactory::create_hdr_texture_attachment(const std::string& name, const Vec2i& size) {
        auto impl = std::make_shared<VulkanAttachmentImpl>(texture_manager, size, HDRColor);

        LOG_INFORMATION("Created Vulkan HDR texture attachment");
        return std::make_shared<IAttachment>(impl, name);
    }

    std::shared_ptr<IAttachment> VulkanAttachmentFactory::create_depth_attachment(const std::string& name, const Vec2i& size) {
        auto impl = std::make_shared<VulkanAttachmentImpl>(texture_manager, size, Depth);

        LOG_INFORMATION("Created Vulkan depth attachment");
        return std::make_shared<IAttachment>(impl, name);
    }
}
