#ifndef _BEBONE_RENDERER_VULKAN_TEXTURE_H_
#define _BEBONE_RENDERER_VULKAN_TEXTURE_H_

#include "itexture.h"

namespace bebone::renderer {
    using namespace bebone::gfx;

    class VulkanTexture : public ITexture {
        private:
            std::shared_ptr<VulkanTextureTuple> texture;

        public:
            VulkanBindlessTextureHandle handle;

            VulkanTexture(std::shared_ptr<VulkanTextureTuple> texture);
            VulkanTexture(const std::string& file_path, std::shared_ptr<gfx::VulkanDevice>& device);

            std::shared_ptr<VulkanTextureTuple>& get_texture();

            TextureHandle get_handle() const override;
    };
}

#endif
