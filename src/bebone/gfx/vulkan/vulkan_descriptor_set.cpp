#include "vulkan_descriptor_set.h"

#include "vulkan_device.h"
#include "vulkan_descriptor_pool.h"
#include "vulkan_descriptor_set_layout.h"

namespace bebone::gfx::vulkan {
    VulkanDescriptorSet::VulkanDescriptorSet(
        std::shared_ptr<VulkanDevice>& device,
        VulkanDescriptorPool& descriptorPool,
        std::shared_ptr<VulkanDescriptorSetLayout>& descriptorSetLayout
    ) {
        VkDescriptorSetAllocateInfo allocInfo{};
        allocInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
        allocInfo.descriptorPool = descriptorPool.backend;
        allocInfo.descriptorSetCount = 1;
        allocInfo.pSetLayouts = &descriptorSetLayout->backend;

        VkDescriptorSetVariableDescriptorCountAllocateInfoEXT countInfo;
        countInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_VARIABLE_DESCRIPTOR_COUNT_ALLOCATE_INFO_EXT;
        countInfo.pNext = nullptr;

        unsigned int maxBinding = 65536 - 1;
        countInfo.descriptorSetCount = 1;

        countInfo.pDescriptorCounts = &maxBinding;
        allocInfo.pNext = &countInfo; // Todo

        // auto& descriptorSet = descriptorSets[descriptorSets.size() - 1];

        if (vkAllocateDescriptorSets(device->device(), &allocInfo, &backend) != VK_SUCCESS) {
            throw std::runtime_error("failed to allocate descriptor sets!");
        }
    }

    void VulkanDescriptorSet::destroy(VulkanDevice& device) {

    }
}
