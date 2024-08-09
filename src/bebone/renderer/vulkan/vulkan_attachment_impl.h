#ifndef _BEBONE_RENDERER_VULKAN_ATTACHMENT_IMPL_H_
#define _BEBONE_RENDERER_VULKAN_ATTACHMENT_IMPL_H_

#include "iattachment_impl.h"
#include "../itexture_manager.h"

namespace bebone::renderer {
    using namespace bebone::gfx;

    class VulkanAttachmentImpl : public IAttachmentImpl {
        private:
            std::vector<TextureHandle> handles;

        public:
            VulkanAttachmentImpl(std::shared_ptr<ITextureManager>& texture_manager, const Vec2i& size, const AttachmentType& type);

            const std::vector<TextureHandle>& get_handles() const;
    };
}

#endif
