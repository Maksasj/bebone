#ifndef _BEBONE_RENDERER_VULKAN_TEXTURE_RESOURCE_H_
#define _BEBONE_RENDERER_VULKAN_TEXTURE_RESOURCE_H_

#include "../itexture_resource.h"

namespace bebone::renderer {
    class VulkanTextureResource : public ITextureResource {
        private:

        public:
            VulkanTextureResource(const std::string& name);

    };
}

#endif
