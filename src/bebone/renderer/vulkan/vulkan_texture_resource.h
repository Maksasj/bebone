#ifndef _BEBONE_RENDERER_VULKAN_TEXTURE_RESOURCE_H_
#define _BEBONE_RENDERER_VULKAN_TEXTURE_RESOURCE_H_

#include "itexture_resource.h"
#include "vulkan_texture.h"

namespace bebone::renderer {
    using namespace bebone::gfx;

    class VulkanTextureResource : public ITextureResource {
        private:
            std::vector<TextureHandle> handles;

        public:
            VulkanTextureResource(const std::string& name, const std::vector<TextureHandle>& handles);

            const std::vector<TextureHandle>& get_handles() const;
    };
}

#endif
