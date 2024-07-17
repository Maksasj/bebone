#ifndef _BEBONE_RENDERER_VULKAN_DEPTH_RESOURCE_H_
#define _BEBONE_RENDERER_VULKAN_DEPTH_RESOURCE_H_

#include "../idepth_resource.h"
#include "vulkan_texture.h"

namespace bebone::renderer {
    using namespace bebone::gfx;

    class VulkanDepthResource : public IDepthResource {
        private:
            std::vector<std::shared_ptr<VulkanTexture>> textures;
            std::vector<VulkanBindlessTextureHandle> handles;

        public:
            VulkanDepthResource(const std::string& name, const std::vector<std::shared_ptr<VulkanTexture>>& textures);

            std::vector<std::shared_ptr<VulkanTexture>>& get_textures();

            const std::vector<VulkanBindlessTextureHandle>& get_handles() const {
                return handles;
            }
    };
}

#endif
