#include "vulkan_attachment_factory.h"

namespace bebone::renderer {
    VulkanAttachmentFactory::VulkanAttachmentFactory(
        const std::shared_ptr<VulkanDevice>& device,
        const std::shared_ptr<ITextureManager>& texture_manager
    ) : device(device), texture_manager(texture_manager) {

    }

    std::shared_ptr<IAttachment> VulkanAttachmentFactory::create_texture_attachment(const std::string& attachment_name, const Vec2i& size) {
        return std::make_shared<IAttachment>(std::make_shared<VulkanAttachmentImpl>(texture_manager, size, Color), attachment_name);
    }

    std::shared_ptr<IAttachment> VulkanAttachmentFactory::create_hdr_texture_attachment(const std::string& attachment_name, const Vec2i& size) {
        return std::make_shared<IAttachment>(std::make_shared<VulkanAttachmentImpl>(texture_manager, size, HDRColor), attachment_name);
    }

    std::shared_ptr<IAttachment> VulkanAttachmentFactory::create_depth_attachment(const std::string& attachment_name, const Vec2i& size) {
        return std::make_shared<IAttachment>(std::make_shared<VulkanAttachmentImpl>(texture_manager, size, Depth), attachment_name);
    }
}
