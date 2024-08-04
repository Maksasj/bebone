#ifndef _BEBONE_RENDERER_VULKAN_DEPTH_ATTACHMENT_H_
#define _BEBONE_RENDERER_VULKAN_DEPTH_ATTACHMENT_H_

#include "idepth_attachment.h"
#include "vulkan_texture_impl.h"

namespace bebone::renderer {
    using namespace bebone::gfx;

    class VulkanDepthAttachment : public IDepthAttachment {
        private:
            std::vector<TextureHandle> handles;

        public:
            VulkanDepthAttachment(const std::string& name, const std::vector<TextureHandle>& handles);

            const std::vector<TextureHandle>& get_handles() const;
    };
}

#endif
