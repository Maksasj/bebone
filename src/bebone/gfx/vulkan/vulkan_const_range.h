#ifndef BEBONE_VULKAN_CONST_RANGE_H
#define BEBONE_VULKAN_CONST_RANGE_H

#include "../gfx_backend.h"

namespace bebone::gfx {
    using namespace bebone::core;

    class VulkanConstRange {
        public:
            VkPushConstantRange range;

            VulkanConstRange(const VkPushConstantRange& range);

            static VulkanConstRange common(const size_t& size, const u32& offset);
    };
}

#endif
