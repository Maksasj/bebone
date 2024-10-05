#include "vulkan_descriptor_set.h"

#include "vulkan_device.h"
#include "vulkan_descriptor_pool.h"
#include "vulkan_descriptor_set_layout.h"

namespace bebone::gfx {
    VulkanDescriptorSet::VulkanDescriptorSet(
        VulkanDevice& device,
        VulkanDescriptorPool& descriptor_pool,
        const std::shared_ptr<VulkanDescriptorSetLayout>& descriptor_set_layout
    ) {
        VkDescriptorSetAllocateInfo alloc_info{};
        alloc_info.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
        alloc_info.descriptorPool = descriptor_pool.backend;
        alloc_info.descriptorSetCount = 1;
        alloc_info.pSetLayouts = &descriptor_set_layout->backend;

        VkDescriptorSetVariableDescriptorCountAllocateInfoEXT count_info;
        count_info.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_VARIABLE_DESCRIPTOR_COUNT_ALLOCATE_INFO_EXT;
        count_info.pNext = nullptr;

        // Todo
        static unsigned int max_binding = 65536 - 1;
        count_info.descriptorSetCount = 1;

        count_info.pDescriptorCounts = &max_binding;
        alloc_info.pNext = &count_info; // Todo

        if (vkAllocateDescriptorSets(device.device, &alloc_info, &backend) != VK_SUCCESS) {
            LOG_ERROR("Failed to allocate descriptor sets");
            throw std::runtime_error("failed to allocate descriptor sets!");
        }

        LOG_TRACE("Allocated Descriptor set");
    }

    /*
    void VulkanDescriptorSet::destroy(VulkanDevice&) {
        // Todo

        mark_destroyed();
    }
    */
}
