#ifndef _BEBONE_GFX_VULKAN_VULKAN_DESCRIPTOR_POOL_H_
#define _BEBONE_GFX_VULKAN_VULKAN_DESCRIPTOR_POOL_H_

#include <vector>

#include "../gfx_backend.h"

#include "vulkan_command_buffer.h"

namespace bebone::gfx::vulkan {
    class VulkanDescriptorSet;
    class VulkanDescriptorSetLayout;

    class VulkanDescriptorPool : public VulkanWrapper<VkDescriptorPool>, private core::NonCopyable {
        public:
            VulkanDescriptorPool(VulkanDevice& device);

            std::shared_ptr<VulkanDescriptorSet> create_descriptor(
                std::shared_ptr<VulkanDevice>& device,
                std::shared_ptr<VulkanDescriptorSetLayout>& descriptorSetLayout);

            std::vector<std::shared_ptr<VulkanDescriptorSet>> create_descriptors(
                std::shared_ptr<VulkanDevice>& device,
                std::shared_ptr<VulkanDescriptorSetLayout>& descriptorSetLayout,
                const size_t& descriptorCount);

            void update_descriptor_set(
                std::shared_ptr<VulkanDevice>& device,
                std::shared_ptr<VulkanBuffer>& buffer,
                const size_t& size,
                std::shared_ptr<VulkanDescriptorSet>& descriptorSet,
                const size_t& binding,
                const size_t& dstArrayElement
            );

            void update_descriptor_set(
                std::shared_ptr<VulkanDevice>& device,
                VulkanBufferMemoryTuple& tuple,
                const size_t& size,
                std::shared_ptr<VulkanDescriptorSet>& descriptorSet,
                const size_t& binding,
                const size_t& dstArrayElement
            );

            void update_descriptor_sets(
                std::shared_ptr<VulkanDevice>& device,
                std::vector<std::shared_ptr<VulkanBuffer>>& buffers,
                const size_t& size,
                std::vector<std::shared_ptr<VulkanDescriptorSet>>& descriptorSets,
                const size_t& binding,
                const std::vector<size_t>& dstArrayElements
            );

            void update_descriptor_sets(
                std::shared_ptr<VulkanDevice>& device,
                std::vector<VulkanBufferMemoryTuple>& tuples,
                const size_t& size,
                std::vector<std::shared_ptr<VulkanDescriptorSet>>& descriptorSets,
                const size_t& binding,
                const std::vector<size_t>& dstArrayElements
            );

            void destroy(VulkanDevice& device) override;
    };  
}

#endif
