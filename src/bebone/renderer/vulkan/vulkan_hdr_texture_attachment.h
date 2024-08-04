#ifndef _BEBONE_RENDERER_VULKAN_HDR_TEXTURE_ATTACHMENT_H_
#define _BEBONE_RENDERER_VULKAN_HDR_TEXTURE_ATTACHMENT_H_

#include "ihdr_texture_attachment.h"
#include "vulkan_texture_impl.h"

namespace bebone::renderer {
    using namespace bebone::gfx;

    class VulkanHDRTextureAttachment : public IHDRTextureAttachment {
        private:
            std::vector<TextureHandle> handles;

        public:
            VulkanHDRTextureAttachment(const std::string& name, const std::vector<TextureHandle>& handles);

            const std::vector<TextureHandle>& get_handles() const;
    };
}

#endif
