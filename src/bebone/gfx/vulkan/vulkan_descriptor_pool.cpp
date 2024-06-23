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
