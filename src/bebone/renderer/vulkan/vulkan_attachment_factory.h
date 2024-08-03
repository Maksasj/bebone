#ifndef _BEBONE_RENDERER_VULKAN_ATTACHMENT_FACTORY_H_
#define _BEBONE_RENDERER_VULKAN_ATTACHMENT_FACTORY_H_

#include "iattachment_factory.h"

#include "vulkan_hdr_texture_attachment.h"
#include "vulkan_depth_attachment.h"
#include "vulkan_texture_attachment.h"
#include "vulkan_texture_manager.h"

namespace bebone::renderer {
    using namespace bebone::gfx;

    class VulkanAttachmentFactory : public IAttachmentFactory {
        private:
            std::shared_ptr<VulkanDevice> device;
            std::shared_ptr<VulkanTextureManager> texture_manager;

        public:
            VulkanAttachmentFactory(const std::shared_ptr<VulkanDevice>& device, const std::shared_ptr<VulkanTextureManager>& texture_manager);

            std::shared_ptr<ITextureAttachment> create_texture_attachment(const std::string& attachment_name, const Vec2i& size) override;
            std::shared_ptr<IHDRTextureAttachment> create_hdr_texture_attachment(const std::string& attachment_name, const Vec2i& size) override;
            std::shared_ptr<IDepthAttachment> create_depth_attachment(const std::string& attachment_name, const Vec2i& size) override;
    };
}

#endif
