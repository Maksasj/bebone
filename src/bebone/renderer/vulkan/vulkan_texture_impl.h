#ifndef _BEBONE_RENDERER_VULKAN_TEXTURE_IMPL_H_
#define _BEBONE_RENDERER_VULKAN_TEXTURE_IMPL_H_

#include "itexture_impl.h"

namespace bebone::renderer {
    using namespace bebone::gfx;

    class VulkanTextureImpl : public ITextureImpl {
        private:
            std::shared_ptr<VulkanTexture> texture;

        public:
            VulkanBindlessTextureHandle handle;

            VulkanTextureImpl(std::shared_ptr<VulkanTexture> texture);
            VulkanTextureImpl(const std::string& file_path, std::shared_ptr<gfx::VulkanDevice>& device);

            std::shared_ptr<VulkanTexture>& get_texture();

            TextureHandle get_handle() const override;
    };
}

#endif
