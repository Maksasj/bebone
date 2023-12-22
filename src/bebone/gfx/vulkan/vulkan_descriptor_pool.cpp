#include "vulkan_descriptor_pool.h"

#include "vulkan_device.h"
#include "vulkan_descriptor_set.h"

namespace bebone::gfx {
    // Todo Count should be pre computed
    VulkanDescriptorPool::VulkanDescriptorPool(VulkanDevice& device) : _device(device) {
        // If vector resizes, then all pointers to descriptors will not be valid

        // descriptorSets.reserve(65536);
        // descriptorSetLayouts.reserve(65536);

        // Todo Why do we need to set type to specific, i wanned to use this also for ssbo
        std::vector<VkDescriptorPoolSize> poolSizes = {
            { VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, 65536 },
            // { VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, maxBindlessResources },
        };

        VkDescriptorPoolCreateInfo poolInfo{};
        poolInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
        poolInfo.poolSizeCount = poolSizes.size();
        poolInfo.pPoolSizes = poolSizes.data();
        poolInfo.maxSets = static_cast<uint32_t>(65536 * poolSizes.size());
        poolInfo.flags = VK_DESCRIPTOR_POOL_CREATE_UPDATE_AFTER_BIND_BIT;

        if (vkCreateDescriptorPool(_device.device(), &poolInfo, nullptr, &descriptorPool) != VK_SUCCESS) {
            throw std::runtime_error("failed to create descriptor pool!");
        }
    }

    VulkanDescriptorPool::~VulkanDescriptorPool() {
        // for(const auto& layouts : descriptorSetLayouts) {
        //     vkDestroyDescriptorSetLayout(_device.device(), layouts, nullptr);
        // }

        vkDestroyDescriptorPool(_device.device(), descriptorPool, nullptr);
    }

    void VulkanDescriptorPool::update_descriptor_sets(std::shared_ptr<VulkanBufferImpl>& buffer, const size_t& size, std::shared_ptr<VulkanDescriptorSet>& descriptorSet, const size_t& binding, const size_t& dstArrayElement) {
        VkDescriptorBufferInfo bufferInfo{};
        bufferInfo.buffer = buffer->get_buffer();
        bufferInfo.offset = 0;
        bufferInfo.range = size;

        VkWriteDescriptorSet descriptorWrite{};
        descriptorWrite.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;

        descriptorWrite.dstSet = descriptorSet->descriptorSet;
        descriptorWrite.dstBinding = binding;
        descriptorWrite.dstArrayElement = dstArrayElement; // Todo THIS IS A HANDLE, and handle counter should work per shader binding, not a cpu binding thing

        descriptorWrite.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
        descriptorWrite.descriptorCount = 1;
        descriptorWrite.pBufferInfo = &bufferInfo;

        descriptorWrite.pImageInfo = nullptr; // Optional
        descriptorWrite.pTexelBufferView = nullptr; // Optional

        vkUpdateDescriptorSets(_device.device(), 1, &descriptorWrite, 0, nullptr);
    }

    std::shared_ptr<VulkanDescriptorSet> VulkanDescriptorPool::create_descriptor_bindless(std::shared_ptr<VulkanDevice>& device, std::shared_ptr<VulkanDescriptorSetLayout>& descriptorSetLayout) {
        return std::make_shared<VulkanDescriptorSet>(device, *this, descriptorSetLayout);
    }
}
