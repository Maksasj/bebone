#include "vulkan_descriptor_pool.h"

#include "vulkan_device.h"
#include "vulkan_descriptor_set.h"

namespace bebone::gfx::vulkan {
    VulkanDescriptorPool::VulkanDescriptorPool(VulkanDevice& device) {
        // Todo Why do we need to set type to specific, i wanned to use this also for ssbo
        std::vector<VkDescriptorPoolSize> poolSizes = {
            { VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, 65536 },
            { VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, 65536 } // Todo combined image sampler
        };

        VkDescriptorPoolCreateInfo poolInfo{};
        poolInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
        poolInfo.poolSizeCount = poolSizes.size();
        poolInfo.pPoolSizes = poolSizes.data();
        poolInfo.maxSets = static_cast<uint32_t>(65536 * poolSizes.size());
        poolInfo.flags = VK_DESCRIPTOR_POOL_CREATE_UPDATE_AFTER_BIND_BIT;

        if (vkCreateDescriptorPool(device.device(), &poolInfo, nullptr, &backend) != VK_SUCCESS) {
            throw std::runtime_error("failed to create descriptor pool!");
        }
    }

    // VulkanDescriptorPool::~VulkanDescriptorPool() {
    //     // for(const auto& layouts : descriptorSetLayouts) {
    //     //     vkDestroyDescriptorSetLayout(_device.device(), layouts, nullptr);
    //     // }
    // }

    void VulkanDescriptorPool::update_descriptor_set(
        std::shared_ptr<VulkanDevice>& device,
        std::shared_ptr<VulkanBuffer>& buffer,
        const size_t& size,
        std::shared_ptr<VulkanDescriptorSet>& descriptorSet,
        const size_t& binding,
        const size_t& dstArrayElement
    ) {
        VkDescriptorBufferInfo bufferInfo{};
        bufferInfo.buffer = buffer->backend;
        bufferInfo.offset = 0;
        bufferInfo.range = size;

        VkWriteDescriptorSet descriptorWrite{};
        descriptorWrite.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;

        descriptorWrite.dstSet = descriptorSet->backend;
        descriptorWrite.dstBinding = binding;
        descriptorWrite.dstArrayElement = dstArrayElement; // Todo THIS IS A HANDLE, and handle counter should work per shader binding, not a cpu binding thing

        descriptorWrite.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
        descriptorWrite.descriptorCount = 1;
        descriptorWrite.pBufferInfo = &bufferInfo;

        descriptorWrite.pImageInfo = nullptr; // Optional
        descriptorWrite.pTexelBufferView = nullptr; // Optional

        vkUpdateDescriptorSets(device->device(), 1, &descriptorWrite, 0, nullptr);
    }

    void VulkanDescriptorPool::update_descriptor_set(
            std::shared_ptr<VulkanDevice>& device,
            std::shared_ptr<VulkanTexture>& texture,
            std::shared_ptr<VulkanDescriptorSet>& descriptorSet,
            const size_t& binding,
            const size_t& dstArrayElement
    ) {
        auto& [image, memory, view, sampler] = *texture;
        update_descriptor_set(device, sampler, view, descriptorSet, binding, dstArrayElement);
    }

    void VulkanDescriptorPool::update_descriptor_set(
            std::shared_ptr<VulkanDevice>& device,
            std::shared_ptr<VulkanSampler>& sampler,
            std::shared_ptr<VulkanImageView>& view,
            std::shared_ptr<VulkanDescriptorSet>& descriptorSet,
            const size_t& binding,
            const size_t& dstArrayElement
    ) {
        VkDescriptorImageInfo imageInfo{};
        imageInfo.sampler = sampler->backend;
        imageInfo.imageView = view->backend;
        imageInfo.imageLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL; // Todo, remove this hard coded cringe

        VkWriteDescriptorSet descriptorWrite{};
        descriptorWrite.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;

        descriptorWrite.dstSet = descriptorSet->backend;
        descriptorWrite.dstBinding = binding;
        descriptorWrite.dstArrayElement = dstArrayElement; // Todo THIS IS A HANDLE, and handle counter should work per shader binding, not a cpu binding thing

        descriptorWrite.descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
        descriptorWrite.descriptorCount = 1;
        // descriptorWrite.pBufferInfo = &bufferInfo;
        descriptorWrite.pImageInfo = &imageInfo;

        // descriptorWrite.pImageInfo = nullptr; // Optional
        descriptorWrite.pTexelBufferView = nullptr; // Optional

        vkUpdateDescriptorSets(device->device(), 1, &descriptorWrite, 0, nullptr);
    }

    void VulkanDescriptorPool::update_descriptor_set(
        std::shared_ptr<VulkanDevice>& device,
        VulkanBufferMemoryTuple& tuple,
        const size_t& size,
        std::shared_ptr<VulkanDescriptorSet>& descriptorSet,
        const size_t& binding,
        const size_t& dstArrayElement
    ) {
        update_descriptor_set(device, tuple.buffer, size, descriptorSet, binding, dstArrayElement);
    }

    void VulkanDescriptorPool::update_descriptor_sets(
            std::shared_ptr<VulkanDevice>& device,
            std::vector<std::shared_ptr<VulkanBuffer>>& buffers,
            const size_t& size,
            std::vector<std::shared_ptr<VulkanDescriptorSet>>& descriptorSets,
            const size_t& binding,
            const std::vector<size_t>& dstArrayElements
    ) {
        if(buffers.size() != dstArrayElements.size())
            throw std::runtime_error("buffer an dstArrayElements count is not matching");

        for(size_t i = 0; i < dstArrayElements.size(); ++i) {
            auto& buffer = buffers[i];
            auto& dstArrayElement = dstArrayElements[i];
            auto& descriptorSet = descriptorSets[i];

            update_descriptor_set(device, buffer, size, descriptorSet, binding, dstArrayElement);
        }
    }

    void VulkanDescriptorPool::update_descriptor_sets(
            std::shared_ptr<VulkanDevice>& device,
            std::vector<VulkanBufferMemoryTuple>& tuples,
            const size_t& size,
            std::vector<std::shared_ptr<VulkanDescriptorSet>>& descriptorSets,
            const size_t& binding,
            const std::vector<size_t>& dstArrayElements
    ) {
        if(tuples.size() != dstArrayElements.size())
            throw std::runtime_error("buffer an dstArrayElements count is not matching");

        for(size_t i = 0; i < dstArrayElements.size(); ++i) {
            auto& buffer = tuples[i].buffer;
            auto& dstArrayElement = dstArrayElements[i];
            auto& descriptorSet = descriptorSets[i];

            update_descriptor_set(device, buffer, size, descriptorSet, binding, dstArrayElement);
        }
    }

    std::shared_ptr<VulkanDescriptorSet> VulkanDescriptorPool::create_descriptor(std::shared_ptr<VulkanDevice>& device, std::shared_ptr<VulkanDescriptorSetLayout>& descriptorSetLayout) {
        return std::make_shared<VulkanDescriptorSet>(device, *this, descriptorSetLayout);
    }

    std::vector<std::shared_ptr<VulkanDescriptorSet>> VulkanDescriptorPool::create_descriptors(std::shared_ptr<VulkanDevice>& device, std::shared_ptr<VulkanDescriptorSetLayout>& descriptorSetLayout, const size_t& descriptorCount) {
        std::vector<std::shared_ptr<VulkanDescriptorSet>> descriptors;

        for(size_t i = 0; i < descriptorCount; ++i)
            descriptors.push_back(std::make_shared<VulkanDescriptorSet>(device, *this, descriptorSetLayout));

        return descriptors;
    }

    void VulkanDescriptorPool::destroy(VulkanDevice& device) {
        vkDestroyDescriptorPool(device.device(), backend, nullptr);
    }
}
