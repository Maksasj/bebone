#include "vulkan_const_range.h"

namespace bebone::gfx {
    using namespace bebone::core;

    VulkanConstRange::VulkanConstRange(const size_t& size, const u32& offset, const VkShaderStageFlags& stage_flags) {
        const_range = VkPushConstantRange{
            .stageFlags = stage_flags,
            .offset = offset,
            .size = static_cast<uint32_t>(size)
        };
    }
}
