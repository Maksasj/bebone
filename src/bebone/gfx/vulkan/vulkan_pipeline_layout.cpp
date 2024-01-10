#include "vulkan_pipeline_layout.h"

#include "vulkan_const_range.h"
#include "vulkan_descriptor_set_layout.h"

namespace bebone::gfx::vulkan {
    VulkanPipelineLayout::VulkanPipelineLayout(
            VulkanDevice& device,
            const std::vector<std::shared_ptr<VulkanDescriptorSetLayout>>& descriptorSetLayouts,
            const std::vector<VulkanConstRange>& constantRanges
        ) {

        std::vector<VkPushConstantRange> ranges;
        for(auto range : constantRanges)
            ranges.push_back(range.range);

        VkPipelineLayoutCreateInfo pipelineLayoutInfo{};
        pipelineLayoutInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;


        std::vector<VkDescriptorSetLayout> layouts;
        for(const auto& layout : descriptorSetLayouts) {
            layouts.push_back(layout->backend);
        }

        pipelineLayoutInfo.setLayoutCount = layouts.size();
        pipelineLayoutInfo.pSetLayouts = layouts.data();
        pipelineLayoutInfo.pushConstantRangeCount = ranges.size();
        pipelineLayoutInfo.pPushConstantRanges = ranges.data();

        if(vkCreatePipelineLayout(device.device(), &pipelineLayoutInfo, nullptr, &backend) != VK_SUCCESS) {
            throw std::runtime_error("Failed to create pipeline layout");
        }
    }

    VkPipelineLayout VulkanPipelineLayout::get_layout() {
        return backend;
    }

    void VulkanPipelineLayout::destroy(VulkanDevice& device) {
        vkDestroyPipelineLayout(device.device(), backend, nullptr);
    }
}
