#ifndef _BEBONE_GFX_VULKAN_CONST_RANGE_H_
#define _BEBONE_GFX_VULKAN_CONST_RANGE_H_

#include "../gfx_backend.h"

namespace bebone::gfx {
    using namespace bebone::core;

    // Todo simplify this class
    class VulkanConstRange {
        public:
            VkPushConstantRange backend;

            VulkanConstRange(const size_t& size, const u32& offset, const VkShaderStageFlags& stage_flags = VK_SHADER_STAGE_ALL);
    };
}

#endif
