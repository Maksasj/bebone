#ifndef BEBONE_VULKAN_PIPELINE_MANAGER_H
#define BEBONE_VULKAN_PIPELINE_MANAGER_H

#include "../gfx_backend.h"

#include "vulkan_device.h"
#include "vulkan_descriptor_pool.h"
#include "vulkan_pipeline_tuples.h"

namespace bebone::gfx::vulkan {
    class VulkanConstRange;

    // Todo inherit from VulkanApi
    class VulkanPipelineManager : private core::NonCopyable {
        private:

        public:
            std::shared_ptr<VulkanDescriptorPool> descriptor_pool; // Todo move to private

            VulkanPipelineManager(VulkanDevice& device);

            VulkanManagedPipelineTuple create_pipeline(std::shared_ptr<VulkanDevice>& device,
                std::shared_ptr<VulkanSwapChain>& swapChain,
                const std::vector<VulkanConstRange>& constantRanges,
                const std::vector<VulkanDescriptorSetLayoutBinding>& bindings,
                VulkanPipelineConfig configInfo
            );

            void destroy(VulkanDevice& device);
    };
}

#endif
