#include "vulkan_descriptor_set.h"

#include "vulkan_descriptor_pool.h"
#include "vulkan_descriptor_set_layout.h"

namespace bebone::gfx {
    VulkanDescriptorSet::VulkanDescriptorSet(std::shared_ptr<VulkanDevice> device, VulkanDescriptorPool& descriptorPool, std::shared_ptr<VulkanDescriptorSetLayout>& descriptorSetLayout) {
        VkDescriptorSetAllocateInfo allocInfo{};
        allocInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
        allocInfo.descriptorPool = descriptorPool.descriptorPool;
        allocInfo.descriptorSetCount = 1;
        allocInfo.pSetLayouts = &descriptorSetLayout->descriptorSetLayout;

        VkDescriptorSetVariableDescriptorCountAllocateInfoEXT countInfo;
        countInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_VARIABLE_DESCRIPTOR_COUNT_ALLOCATE_INFO_EXT;
        countInfo.pNext = nullptr;

        unsigned int maxBinding = maxBindlessResources - 1;
        countInfo.descriptorSetCount = 1;

        countInfo.pDescriptorCounts = &maxBinding;
        allocInfo.pNext = &countInfo; // Todo

        // auto& descriptorSet = descriptorSets[descriptorSets.size() - 1];

        /** Aka taking last */
        if (vkAllocateDescriptorSets(device->device(), &allocInfo, &descriptorSet) != VK_SUCCESS) {
            throw std::runtime_error("failed to allocate descriptor sets!");
        }
    }
}
