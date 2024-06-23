#ifndef BEBONE_VULKAN_PIPELINE_MANAGER_H
#define BEBONE_VULKAN_PIPELINE_MANAGER_H

#include "../gfx_backend.h"

#include "vulkan_device.h"
#include "vulkan_descriptor_pool.h"

namespace bebone::gfx::vulkan {
    class VulkanConstRange;

    struct VulkanManagedPipelineTuple : public VulkanApi {
        std::shared_ptr<VulkanPipeline> pipeline;
        std::shared_ptr<VulkanPipelineLayout> layout;
        std::vector<std::shared_ptr<VulkanDescriptorSet>> descriptors;

        void destroy(VulkanDevice &device) override;
    };

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
