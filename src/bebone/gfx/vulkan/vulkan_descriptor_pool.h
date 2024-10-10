#ifndef _BEBONE_GFX_VULKAN_DESCRIPTOR_POOL_H_
#define _BEBONE_GFX_VULKAN_DESCRIPTOR_POOL_H_

#include <vector>

#include "../gfx_backend.h"

#include "vulkan_command_buffer.h"

namespace bebone::gfx {
    class VulkanDescriptorSet;
    class VulkanDescriptorSetLayout;

    class VulkanDescriptorPool : private core::NonCopyable {
        public:
            VkDescriptorPool backend;

        private:
            VulkanDevice& device_owner;

        public:
            VulkanDescriptorPool(VulkanDevice& device);
            ~VulkanDescriptorPool();

            std::unique_ptr<VulkanDescriptorSet> create_descriptor(const std::unique_ptr<VulkanDescriptorSetLayout>& descriptor_set_layout);
            std::vector<std::unique_ptr<VulkanDescriptorSet>> create_descriptors(const std::unique_ptr<VulkanDescriptorSetLayout>& descriptor_set_layout, const size_t& count);
    };
}

#endif
