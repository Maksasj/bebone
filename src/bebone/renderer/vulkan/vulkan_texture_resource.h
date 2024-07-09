#ifndef _BEBONE_RENDERER_VULKAN_TEXTURE_RESOURCE_H_
#define _BEBONE_RENDERER_VULKAN_TEXTURE_RESOURCE_H_

#include "../itexture_resource.h"

namespace bebone::renderer {
    using namespace bebone::gfx;

    class VulkanTextureResource : public ITextureResource {
        private:
            std::vector<std::shared_ptr<VulkanTexture>> textures;

        public:
            VulkanTextureResource(const std::string& name, std::shared_ptr<VulkanDevice>& device);

    };
}

#endif
