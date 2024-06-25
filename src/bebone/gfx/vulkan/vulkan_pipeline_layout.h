#ifndef _BEBONE_GFX_VULKAN_PIPELINE_LAYOUT_H_
#define _BEBONE_GFX_VULKAN_PIPELINE_LAYOUT_H_

#include "../gfx_backend.h"

#include "vulkan_device.h"
#include "vulkan_descriptor_pool.h"

namespace bebone::gfx::vulkan {
    class VulkanConstRange;

    class VulkanPipelineLayout : public VulkanWrapper<VkPipelineLayout>, private core::NonCopyable {
        public:
            VulkanPipelineLayout(
                VulkanDevice& device,
                const std::vector<std::shared_ptr<VulkanDescriptorSetLayout>>& descriptorSetLayouts,
                const std::vector<VulkanConstRange>& constant_ranges
            );

            VkPipelineLayout get_layout();

            void destroy(VulkanDevice& device) override;
    };
}

#endif
