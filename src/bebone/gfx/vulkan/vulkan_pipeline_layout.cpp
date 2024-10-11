#include "vulkan_pipeline_layout.h"

#include "vulkan_const_range.h"
#include "vulkan_descriptor_set_layout.h"

namespace bebone::gfx {
    VulkanPipelineLayout::VulkanPipelineLayout(
            IVulkanDevice& device,
            const std::vector<std::unique_ptr<VulkanDescriptorSetLayout>>& descriptor_set_layouts,
            const std::vector<VulkanConstRange>& constant_ranges
        ) : device_owner(device) {
        auto ranges = std::vector<VkPushConstantRange> {};
        ranges.reserve(constant_ranges.size());

        for(const auto& range : constant_ranges)
            ranges.push_back(range.const_range);

        auto layouts = std::vector<VkDescriptorSetLayout> {};
        layouts.reserve(descriptor_set_layouts.size());

        for(const auto& layout : descriptor_set_layouts)
            layouts.push_back(layout->descriptor_set_layout);

        VkPipelineLayoutCreateInfo pipeline_layout_info{};

        pipeline_layout_info.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
        pipeline_layout_info.setLayoutCount = layouts.size();
        pipeline_layout_info.pSetLayouts = layouts.data();
        pipeline_layout_info.pushConstantRangeCount = ranges.size();
        pipeline_layout_info.pPushConstantRanges = ranges.data();

        if(vkCreatePipelineLayout(device_owner.get_vk_device(), &pipeline_layout_info, nullptr, &pipeline_layout) != VK_SUCCESS) {
            LOG_ERROR("Failed to create pipeline layout");
            throw std::runtime_error("Failed to create pipeline layout");
        }

        LOG_TRACE("Created Vulkan pipeline layout");
    }

    VulkanPipelineLayout::~VulkanPipelineLayout() {
        vkDestroyPipelineLayout(device_owner.get_vk_device(), pipeline_layout, nullptr);

        LOG_TRACE("Destroyed Vulkan pipeline layout");
    }
}
