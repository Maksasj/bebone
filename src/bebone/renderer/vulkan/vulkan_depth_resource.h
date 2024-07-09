#ifndef _BEBONE_RENDERER_VULKAN_DEPTH_RESOURCE_H_
#define _BEBONE_RENDERER_VULKAN_DEPTH_RESOURCE_H_

#include "../idepth_resource.h"

namespace bebone::renderer {
    class VulkanDepthResource : public IDepthResource {
        private:

        public:
            VulkanDepthResource(const std::string& name);

    };
}

#endif
