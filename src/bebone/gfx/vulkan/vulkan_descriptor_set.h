#ifndef _BEBONE_GFX_VULKAN_DESCRIPTOR_SET_H_
#define _BEBONE_GFX_VULKAN_DESCRIPTOR_SET_H_

#include <memory>

#include "../gfx_backend.h"

#include "interface/i_vulkan_buffer.h"
#include "interface/i_vulkan_sampler.h"
#include "interface/i_vulkan_image_view.h"
#include "interface/i_vulkan_device.h"

namespace bebone::gfx {
    class VulkanDescriptorPool;
    class VulkanDescriptorSetLayout;

    class VulkanDescriptorSet : private core::NonCopyable {
        public:
            IVulkanDevice& device_owner;
            VkDescriptorSet backend;

        public:
            VulkanDescriptorSet(
                IVulkanDevice& device,
                VulkanDescriptorPool& descriptor_pool,
                const std::unique_ptr<VulkanDescriptorSetLayout>& descriptor_set_layout);

            void update_descriptor_set(IVulkanBuffer& buffer, const size_t& binding, const size_t& dst_array_element);
            void update_descriptor_set(IVulkanSampler& sampler, IVulkanImageView& view, const size_t& binding, const size_t& dst_array_element);
    };
}

#endif
