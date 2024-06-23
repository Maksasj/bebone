#ifndef _BEBONE_GFX_VULKAN_BUFFER_TUPLES_H_
#define _BEBONE_GFX_VULKAN_BUFFER_TUPLES_H_

#include <vector>

#include "../gfx_backend.h"

#include "vulkan_buffer.h"

namespace bebone::gfx::vulkan {
    using namespace bebone::core;

    struct VulkanBufferMemoryTuple : public VulkanApi {
        std::shared_ptr<VulkanBuffer> buffer;
        std::shared_ptr<VulkanDeviceMemory> memory;

        VulkanBufferMemoryTuple(
            const shared_ptr<VulkanBuffer>& buffer,
            const shared_ptr<VulkanDeviceMemory>& memory);

        void destroy(VulkanDevice &device) override;
    };
}

#endif
