#ifndef _BEBONE_RENDERER_VULKAN_ATTACHMENT_IMPL_H_
#define _BEBONE_RENDERER_VULKAN_ATTACHMENT_IMPL_H_

#include "iattachment_impl.h"

namespace bebone::renderer {
    using namespace bebone::gfx;

    class VulkanAttachmentImpl : public IAttachmentImpl {
        private:
            std::vector<TextureHandle> handles;

        public:
            VulkanAttachmentImpl(const std::vector<TextureHandle>& handles);

            const std::vector<TextureHandle>& get_handles() const;
    };
}

#endif
