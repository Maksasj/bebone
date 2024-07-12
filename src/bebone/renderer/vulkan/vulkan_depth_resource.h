#ifndef _BEBONE_RENDERER_VULKAN_DEPTH_RESOURCE_H_
#define _BEBONE_RENDERER_VULKAN_DEPTH_RESOURCE_H_

#include "../idepth_resource.h"

namespace bebone::renderer {
    using namespace bebone::gfx;

    class VulkanDepthResource : public IDepthResource {
        private:
            std::vector<std::shared_ptr<VulkanDepthImageTuple>> depth_textures;

        public:
            VulkanDepthResource(const std::string& name, const Vec2i& size, std::shared_ptr<VulkanDevice>& device);

            std::vector<std::shared_ptr<VulkanDepthImageTuple>>& get_textures();
    };
}

#endif
