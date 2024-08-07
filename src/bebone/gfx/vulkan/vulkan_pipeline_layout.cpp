#include "vulkan_pipeline_layout.h"

#include "vulkan_const_range.h"
#include "vulkan_descriptor_set_layout.h"

namespace bebone::gfx {
    VulkanPipelineLayout::VulkanPipelineLayout(
            VulkanDevice& device,
            const std::vector<std::shared_ptr<VulkanDescriptorSetLayout>>& descriptor_set_layouts,
            const std::vector<VulkanConstRange>& constant_ranges
        ) {
        auto ranges = std::vector<VkPushConstantRange> {};
        ranges.reserve(constant_ranges.size());

        for(const auto& range : constant_ranges)
            ranges.push_back(range.backend);

        auto layouts = std::vector<VkDescriptorSetLayout> {};
        layouts.reserve(descriptor_set_layouts.size());

        for(const auto& layout : descriptor_set_layouts)
            layouts.push_back(layout->backend);

        VkPipelineLayoutCreateInfo pipeline_layout_info{};

        pipeline_layout_info.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
        pipeline_layout_info.setLayoutCount = layouts.size();
        pipeline_layout_info.pSetLayouts = layouts.data();
        pipeline_layout_info.pushConstantRangeCount = ranges.size();
        pipeline_layout_info.pPushConstantRanges = ranges.data();

        if(vkCreatePipelineLayout(device.device, &pipeline_layout_info, nullptr, &backend) != VK_SUCCESS)
            throw std::runtime_error("Failed to create pipeline layout");
    }

    void VulkanPipelineLayout::destroy(VulkanDevice& device) {
        if(is_destroyed())
            return;

        vkDestroyPipelineLayout(device.device, backend, nullptr);

        mark_destroyed();
    }
}
