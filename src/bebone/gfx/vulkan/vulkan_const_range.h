#ifndef _BEBONE_GFX_VULKAN_VULKAN_CONST_RANGE_H_
#define _BEBONE_GFX_VULKAN_VULKAN_CONST_RANGE_H_

#include "../gfx_backend.h"

namespace bebone::gfx::vulkan {
    using namespace bebone::core;

    class VulkanConstRange {
        public:
            VkPushConstantRange range;

            VulkanConstRange(const VkPushConstantRange& range);

            static VulkanConstRange common(const size_t& size, const u32& offset);
    };
}

#endif
