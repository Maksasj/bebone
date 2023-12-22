#ifndef _BEBONE_GFX_VULKAN_PIPELINE_LAYOUT_IMPLEMENTATION_H_
#define _BEBONE_GFX_VULKAN_PIPELINE_LAYOUT_IMPLEMENTATION_H_

#include "vulkan_device.h"
#include "../gfx_backend.h"

#include "vulkan_descriptor_pool.h"

namespace bebone::gfx {
    class VulkanPipelineLayoutImpl {
        private:
            VkPipelineLayout pipelineLayout;

        public:
            VulkanPipelineLayoutImpl(
                VulkanDevice& device,
                const std::vector<std::shared_ptr<VulkanDescriptorSetLayout>>& descriptorSetLayouts,
                const std::vector<VkPushConstantRange>& constantRanges
            );

            ~VulkanPipelineLayoutImpl();

            VkPipelineLayout get_layout();
    };
}

#endif
