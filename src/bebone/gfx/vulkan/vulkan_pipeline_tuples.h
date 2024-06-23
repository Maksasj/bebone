#ifndef BEBONE_VULKAN_PIPELINE_TUPLES_H
#define BEBONE_VULKAN_PIPELINE_TUPLES_H

#include "../gfx_backend.h"

#include "vulkan_pipeline.h"
#include "vulkan_descriptor_set.h"

namespace bebone::gfx::vulkan {
    class VulkanConstRange;

    struct VulkanManagedPipelineTuple : public VulkanApi {
        std::shared_ptr<VulkanPipeline> pipeline;
        std::shared_ptr<VulkanPipelineLayout> layout;
        std::vector<std::shared_ptr<VulkanDescriptorSet>> descriptors;

        VulkanManagedPipelineTuple(
            const shared_ptr<VulkanPipeline>& pipeline,
            const shared_ptr<VulkanPipelineLayout>& layout,
            const std::vector<std::shared_ptr<VulkanDescriptorSet>> & descriptors);

        void destroy(VulkanDevice &device) override;
    };
}

#endif
