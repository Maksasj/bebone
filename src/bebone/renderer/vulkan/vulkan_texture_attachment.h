#ifndef _BEBONE_RENDERER_VULKAN_TEXTURE_ATTACHMENT_H_
#define _BEBONE_RENDERER_VULKAN_TEXTURE_ATTACHMENT_H_

#include "itexture_attachment.h"
#include "vulkan_texture_impl.h"

namespace bebone::renderer {
    using namespace bebone::gfx;

    class VulkanTextureAttachment : public ITextureAttachment {
        private:
            std::vector<TextureHandle> handles;

        public:
            VulkanTextureAttachment(const std::string& name, const std::vector<TextureHandle>& handles);

            const std::vector<TextureHandle>& get_handles() const;
    };
}

#endif
