#ifndef _BEBONE_VULKAN_PIPELINE_MANAGER_H_
#define _BEBONE_VULKAN_PIPELINE_MANAGER_H_

#include "../gfx_backend.h"

#include "vulkan_device.h"
#include "vulkan_descriptor_pool.h"

namespace bebone::gfx::vulkan {
    class VulkanConstRange;

    using VulkanManagedPipelineTuple = tuple<std::shared_ptr<VulkanPipeline>, std::shared_ptr<VulkanPipelineLayout>, std::vector<std::shared_ptr<VulkanDescriptorSet>>>;

    class VulkanPipelineManager : public VulkanApi, private core::NonCopyable {
        private:

        public:
            std::shared_ptr<VulkanDescriptorPool> descriptor_pool; // Todo move to private

            VulkanPipelineManager(VulkanDevice& device);

            VulkanManagedPipelineTuple create_pipeline(std::shared_ptr<VulkanDevice>& device,
                std::shared_ptr<VulkanSwapChain>& swap_chain,
                const std::vector<VulkanConstRange>& constant_ranges,
                const std::vector<VulkanDescriptorSetLayoutBinding>& bindings,
                VulkanPipelineConfig config_info
            );

            void destroy(VulkanDevice& device) override;
    };
}

#endif
