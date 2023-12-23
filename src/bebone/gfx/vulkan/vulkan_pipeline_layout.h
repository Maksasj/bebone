#ifndef _BEBONE_GFX_vulkan_pipeline_layoutEMENTATION_H_
#define _BEBONE_GFX_vulkan_pipeline_layoutEMENTATION_H_

#include "vulkan_device.h"
#include "../gfx_backend.h"

#include "vulkan_descriptor_pool.h"

namespace bebone::gfx {
    class VulkanPipelineLayout : private core::NonCopyable {
        private:
            VkPipelineLayout pipelineLayout;

        public:
            VulkanPipelineLayout(
                VulkanDevice& device,
                const std::vector<std::shared_ptr<VulkanDescriptorSetLayout>>& descriptorSetLayouts,
                const std::vector<VkPushConstantRange>& constantRanges
            );

            ~VulkanPipelineLayout();

            VkPipelineLayout get_layout();
    };
}

#endif
