#include "vulkan_wrapper.tpp"

namespace bebone::gfx::vulkan {
    void VulkanApi::mark_destroyed() {
        destroyed = true;
    }

    const bool& VulkanApi::is_destroyed() const {
        return destroyed;
    }
}
