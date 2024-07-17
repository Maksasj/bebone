#include "vulkan_descriptor_pool.h"

#include "vulkan_texture_tuple.h"
#include "vulkan_device.h"
#include "vulkan_descriptor_set.h"

namespace bebone::gfx {
    VulkanDescriptorPool::VulkanDescriptorPool(VulkanDevice& device) {
        // Todo Why do we need to set type to specific, i wanned to use this also for ssbo
        auto pool_sizes = std::vector<VkDescriptorPoolSize> {
            { VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, 65536 },
            { VK_DESCRIPTOR_TYPE_STORAGE_BUFFER, 65536 },
            { VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, 65536 }
        };

        VkDescriptorPoolCreateInfo pool_info{};

        pool_info.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
        pool_info.poolSizeCount = pool_sizes.size();
        pool_info.pPoolSizes = pool_sizes.data();
        pool_info.maxSets = static_cast<uint32_t>(65536 * pool_sizes.size());
        pool_info.flags = VK_DESCRIPTOR_POOL_CREATE_UPDATE_AFTER_BIND_BIT;

        if(vkCreateDescriptorPool(device.device, &pool_info, nullptr, &backend) != VK_SUCCESS)
            throw std::runtime_error("failed to create descriptor pool!");
    }

    std::shared_ptr<VulkanDescriptorSet> VulkanDescriptorPool::create_descriptor(
        VulkanDevice& device,
        const std::shared_ptr<VulkanDescriptorSetLayout>& descriptor_set_layout
    ) {
        return std::make_shared<VulkanDescriptorSet>(device, *this, descriptor_set_layout);
    }

    std::vector<std::shared_ptr<VulkanDescriptorSet>> VulkanDescriptorPool::create_descriptors(
        std::shared_ptr<VulkanDevice>& device,
        const std::shared_ptr<VulkanDescriptorSetLayout>& descriptor_set_layout,
        const size_t& count
    ) {
        auto descriptors = std::vector<std::shared_ptr<VulkanDescriptorSet>>{};
        descriptors.reserve(count);

        for(size_t i = 0; i < count; ++i)
            descriptors.push_back(std::make_shared<VulkanDescriptorSet>(*device, *this, descriptor_set_layout));

        return descriptors;
    }

    void VulkanDescriptorPool::destroy(VulkanDevice& device) {
        if(is_destroyed())
            return;
        
        vkDestroyDescriptorPool(device.device, backend, nullptr);

        mark_destroyed();
    }
}
