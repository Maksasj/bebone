#include "vulkan_pipeline_layout_impl.h"

namespace bebone::gfx {
    VulkanPipelineLayoutImpl::VulkanPipelineLayoutImpl(VulkanDevice& device, VulkanDescriptorPool& descriptorPool, const std::vector<VkPushConstantRange>& constantRanges) : _device(device) {
        VkPipelineLayoutCreateInfo pipelineLayoutInfo{};
        pipelineLayoutInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;

        pipelineLayoutInfo.setLayoutCount = descriptorPool.get_layouts_count(); // This thing should be computed from created descriptor sets, for now there is just constants
        pipelineLayoutInfo.pSetLayouts = descriptorPool.get_layouts_data(); // This thing should be computed from created descriptor sets, for now there is just constants
        pipelineLayoutInfo.pushConstantRangeCount = constantRanges.size();
        pipelineLayoutInfo.pPushConstantRanges = constantRanges.data();

        if(vkCreatePipelineLayout(_device.device(), &pipelineLayoutInfo, nullptr, &pipelineLayout) != VK_SUCCESS) {
            throw std::runtime_error("Failed to create pipeline layout");
        }
    }

    VkPipelineLayout VulkanPipelineLayoutImpl::get_layout() {
        return pipelineLayout;
    }

    VulkanPipelineLayoutImpl::~VulkanPipelineLayoutImpl() {
        vkDestroyPipelineLayout(_device.device(), pipelineLayout, nullptr);
    }
}
