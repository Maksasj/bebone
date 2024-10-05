#ifndef _BEBONE_GFX_VULKAN_SAMPLER_H_
#define _BEBONE_GFX_VULKAN_SAMPLER_H_

#include <vector>

#include "../gfx_backend.h"

#include "vulkan_wrapper.tpp"
#include "vulkan_device_memory.h"

namespace bebone::gfx {
    class VulkanDevice;

    using namespace bebone::core;

    class VulkanSampler : public VulkanWrapper<VkSampler>, private core::NonCopyable {
        public:
            VulkanSampler(VulkanDevice& device);

            // void destroy(VulkanDevice& device) override;
    };
}

#endif
