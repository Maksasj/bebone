#include "vulkan_const_range.h"

namespace bebone::gfx {
    using namespace bebone::core;

    VulkanConstRange::VulkanConstRange(const size_t& size, const u32& offset) {
        backend = VkPushConstantRange{
            .stageFlags = VK_SHADER_STAGE_ALL, // Todo
            .offset = offset,
            .size = static_cast<uint32_t>(size)
        };
    }
}
