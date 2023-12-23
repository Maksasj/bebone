#include "vulkan_result.h"

namespace bebone::gfx {
    VulkanResult::VulkanResult(const VkResult& result) : result(result) {

    }

    VulkanResult VulkanResult::ok() {
        return VulkanResult(VK_SUCCESS);
    }

    bool VulkanResult::is_ok() {
        return (result == VK_ERROR_OUT_OF_DATE_KHR) || (result == VK_SUBOPTIMAL_KHR);
    }
}
