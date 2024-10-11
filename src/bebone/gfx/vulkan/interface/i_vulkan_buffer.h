#ifndef _BEBONE_GFX_I_VULKAN_BUFFER_H_
#define _BEBONE_GFX_I_VULKAN_BUFFER_H_

#include "../../gfx_backend.h"

#include "i_vulkan_image.h"

namespace bebone::gfx {
    using namespace bebone::core;

    class IVulkanBuffer {
        public:
            [[nodiscard]] virtual VkBuffer get_vk_buffer() const = 0;
            [[nodiscard]] virtual VkMemoryRequirements get_memory_requirements() const = 0;
            [[nodiscard]] virtual size_t get_size() const = 0;
            virtual void copy_to_image(IVulkanImage& image) = 0;
    };
}

#endif
