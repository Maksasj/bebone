#include "vulkan_const_range.h"

namespace bebone::gfx {
    using namespace bebone::core;

    VulkanConstRange::VulkanConstRange(const VkPushConstantRange& range) {
        backend = range;
    }

    VulkanConstRange VulkanConstRange::common(const size_t& size, const u32& offset) {
        return VulkanConstRange( VkPushConstantRange{
            .stageFlags = (VK_SHADER_STAGE_VERTEX_BIT | VK_SHADER_STAGE_FRAGMENT_BIT),
            .offset = offset,
            .size = static_cast<uint32_t>(size)
        });
    }

    void VulkanConstRange::destroy(VulkanDevice& device) {
        std::ignore = device;
    }
}
