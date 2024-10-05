#include "vulkan_const_range.h"

namespace bebone::gfx {
    using namespace bebone::core;

    VulkanConstRange::VulkanConstRange(const size_t& size, const u32& offset, const VkShaderStageFlags& stage_flags) {
        backend = VkPushConstantRange{
            .stageFlags = stage_flags,
            .offset = offset,
            .size = static_cast<uint32_t>(size)
        };
    }

    /*
    void VulkanConstRange::destroy(VulkanDevice& device) {
        std::ignore = device;
    }
    */
}
