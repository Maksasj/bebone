#include "vulkan_descriptor_pool.h"

#include "vulkan_texture_tuple.h"
#include "vulkan_device.h"
#include "vulkan_descriptor_set.h"

namespace bebone::gfx {
    VulkanDescriptorPool::VulkanDescriptorPool(IVulkanDevice& device) : device_owner(device) {
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

        if(vkCreateDescriptorPool(device_owner.get_vk_device(), &pool_info, nullptr, &descriptor_pool) != VK_SUCCESS) {
            LOG_ERROR("Failed to create descriptor pool");
            throw std::runtime_error("failed to create descriptor pool!");
        }

        LOG_TRACE("Created Descriptor pool");
    }

    VulkanDescriptorPool::~VulkanDescriptorPool() {
        vkDestroyDescriptorPool(device_owner.get_vk_device(), descriptor_pool, nullptr);

        LOG_TRACE("Destroyed Descriptor pool");
    }

    std::unique_ptr<VulkanDescriptorSet> VulkanDescriptorPool::create_descriptor(
        const std::unique_ptr<VulkanDescriptorSetLayout>& descriptor_set_layout
    ) {
        return std::make_unique<VulkanDescriptorSet>(device_owner, *this, descriptor_set_layout);
    }

    std::vector<std::unique_ptr<VulkanDescriptorSet>> VulkanDescriptorPool::create_descriptors(
        const std::unique_ptr<VulkanDescriptorSetLayout>& descriptor_set_layout,
        const size_t& count
    ) {
        auto descriptors = std::vector<std::unique_ptr<VulkanDescriptorSet>>{};
        descriptors.reserve(count);

        for(size_t i = 0; i < count; ++i)
            descriptors.push_back(std::make_unique<VulkanDescriptorSet>(device_owner, *this, descriptor_set_layout));

        return descriptors;
    }
}
