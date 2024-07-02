#ifndef _BEBONE_GFX_VULKAN_CONST_RANGE_H_
#define _BEBONE_GFX_VULKAN_CONST_RANGE_H_

#include "../gfx_backend.h"

#include "vulkan_wrapper.tpp"

namespace bebone::gfx {
    using namespace bebone::core;

    class VulkanConstRange : public VulkanWrapper<VkPushConstantRange> {
        public:
            VulkanConstRange(const VkPushConstantRange& range);

            static VulkanConstRange common(const size_t& size, const u32& offset);

            void destroy(VulkanDevice& device) override;
    };
}

#endif
