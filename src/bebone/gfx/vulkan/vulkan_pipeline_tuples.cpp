#include "vulkan_pipeline_tuples.h"

namespace bebone::gfx::vulkan {
    VulkanManagedPipelineTuple::VulkanManagedPipelineTuple(
        const shared_ptr<VulkanPipeline>& pipeline,
        const shared_ptr<VulkanPipelineLayout>& layout,
        const std::vector<std::shared_ptr<VulkanDescriptorSet>> & descriptors
    ) : pipeline(pipeline), layout(layout), descriptors(descriptors) {

    }

    void VulkanManagedPipelineTuple::destroy(VulkanDevice &device) {

    }
}
