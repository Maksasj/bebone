#ifndef _BEBONE_GFX_VULKAN_PIPELINE_LAYOUT_H_
#define _BEBONE_GFX_VULKAN_PIPELINE_LAYOUT_H_

#include "../gfx_backend.h"

#include "vulkan_device.h"
#include "vulkan_descriptor_pool.h"

namespace bebone::gfx {
    class VulkanConstRange;

    class VulkanPipelineLayout : private core::NonCopyable {
        public:
            VkPipelineLayout backend;

        private:
            VulkanDevice& device_owner;

        public:
            VulkanPipelineLayout(
                VulkanDevice& device,
                const std::vector<std::unique_ptr<VulkanDescriptorSetLayout>>& descriptor_set_layouts,
                const std::vector<VulkanConstRange>& constant_ranges);

            ~VulkanPipelineLayout();

            // void destroy(VulkanDevice& device) override;
    };
}

#endif
