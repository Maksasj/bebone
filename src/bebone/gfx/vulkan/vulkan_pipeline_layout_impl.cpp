#include "vulkan_pipeline_layout_impl.h"

#include "vulkan_descriptor_set_layout.h"

namespace bebone::gfx {
    VulkanPipelineLayoutImpl::VulkanPipelineLayoutImpl(
            VulkanDevice& device,
            const std::vector<std::shared_ptr<VulkanDescriptorSetLayout>>& descriptorSetLayouts,
            const std::vector<VkPushConstantRange>& constantRanges
        ) {

        VkPipelineLayoutCreateInfo pipelineLayoutInfo{};
        pipelineLayoutInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;

        std::vector<VkDescriptorSetLayout> layouts;
        for(const auto& layout : descriptorSetLayouts) {
            layouts.push_back(layout->descriptorSetLayout);
        }

        pipelineLayoutInfo.setLayoutCount = layouts.size();
        pipelineLayoutInfo.pSetLayouts = layouts.data();
        pipelineLayoutInfo.pushConstantRangeCount = constantRanges.size();
        pipelineLayoutInfo.pPushConstantRanges = constantRanges.data();

        if(vkCreatePipelineLayout(device.device(), &pipelineLayoutInfo, nullptr, &pipelineLayout) != VK_SUCCESS) {
            throw std::runtime_error("Failed to create pipeline layout");
        }
    }

    VkPipelineLayout VulkanPipelineLayoutImpl::get_layout() {
        return pipelineLayout;
    }

    VulkanPipelineLayoutImpl::~VulkanPipelineLayoutImpl() {
        // vkDestroyPipelineLayout(_device.device(), pipelineLayout, nullptr);
    }
}
