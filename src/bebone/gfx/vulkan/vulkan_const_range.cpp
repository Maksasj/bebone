#include "vulkan_const_range.h"

namespace bebone::gfx::vulkan {
    using namespace bebone::core;

    VulkanConstRange::VulkanConstRange(const VkPushConstantRange& range) : range(range) {

    }

    VulkanConstRange VulkanConstRange::common(const size_t& size, const u32& offset) {
        return VulkanConstRange({
            .stageFlags = (VK_SHADER_STAGE_VERTEX_BIT | VK_SHADER_STAGE_FRAGMENT_BIT),
            .offset = offset,
            .size = static_cast<uint32_t>(size)
        });
    }
}
