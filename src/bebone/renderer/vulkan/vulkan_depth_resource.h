#ifndef _BEBONE_RENDERER_VULKAN_DEPTH_RESOURCE_H_
#define _BEBONE_RENDERER_VULKAN_DEPTH_RESOURCE_H_

#include "../idepth_resource.h"
#include "vulkan_texture.h"

namespace bebone::renderer {
    using namespace bebone::gfx;

    class VulkanDepthResource : public IDepthResource {
        private:
            std::vector<TextureHandle> handles;

        public:
            VulkanDepthResource(const std::string& name, const std::vector<TextureHandle>& handles);

            const std::vector<TextureHandle>& get_handles() const;
    };
}

#endif
