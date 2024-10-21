#ifndef _BEBONE_GFX_I_VULKAN_SAMPLER_H_
#define _BEBONE_GFX_I_VULKAN_SAMPLER_H_

#include "../../gfx_backend.h"

namespace bebone::gfx {
    using namespace bebone::core;

    class IVulkanSampler {
        private:
        public:
            virtual ~IVulkanSampler() = default;

            virtual VkSampler get_vk_image_sampler() const = 0;
    };
}

#endif