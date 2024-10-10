#ifndef _BEBONE_GFX_VULKAN_DESCRIPTOR_SET_H_
#define _BEBONE_GFX_VULKAN_DESCRIPTOR_SET_H_

#include <memory>

#include "../gfx_backend.h"

namespace bebone::gfx {
    class VulkanDevice;
    class VulkanDescriptorPool;
    class VulkanDescriptorSetLayout;

    class VulkanDescriptorSet : private core::NonCopyable {
        public:
            VkDescriptorSet backend;

        public:
            VulkanDescriptorSet(
                VulkanDevice& device,
                VulkanDescriptorPool& descriptor_pool,
                const std::unique_ptr<VulkanDescriptorSetLayout>& descriptor_set_layout);

            // void destroy(VulkanDevice& device) override;
    };
}

#endif
