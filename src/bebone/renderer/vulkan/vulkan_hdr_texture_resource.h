#ifndef _BEBONE_RENDERER_VULKAN_HDR_TEXTURE_RESOURCE_H_
#define _BEBONE_RENDERER_VULKAN_HDR_TEXTURE_RESOURCE_H_

#include "../ihdr_texture_resource.h"

namespace bebone::renderer {
    using namespace bebone::gfx;

    class VulkanHDRTextureResource : public IHDRTextureResource {
        private:
            std::vector<std::shared_ptr<VulkanTexture>> textures;

        public:
            VulkanHDRTextureResource(const std::string& name, const Vec2i& size, std::shared_ptr<VulkanDevice>& device);

            std::vector<std::shared_ptr<VulkanTexture>>& get_textures();
    };
}

#endif
