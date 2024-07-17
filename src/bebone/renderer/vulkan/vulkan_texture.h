#ifndef _BEBONE_RENDERER_VULKAN_TEXTURE_H_
#define _BEBONE_RENDERER_VULKAN_TEXTURE_H_

#include "../itexture.h"

namespace bebone::renderer {
    using namespace bebone::gfx;

    class VulkanTexture : public ITexture {
        private:
            std::shared_ptr<VulkanTextureTuple> texture;

        public:
            VulkanBindlessTextureHandle handle;

            VulkanTexture(const std::string& file_path, std::shared_ptr<gfx::VulkanDevice>& device);

            std::shared_ptr<VulkanTextureTuple>& get_texture();

            const VulkanBindlessTextureHandle& get_handle() const;
    };
}

#endif
