#ifndef _BEBONE_GFX_VULKAN_DEVICE_H_
#define _BEBONE_GFX_VULKAN_DEVICE_H_

#include <iostream>
#include <set>
#include <unordered_set>

#include "../gfx_backend.h"
#include "../window/window.h"

#include "../shaders/shader_type.h"
#include "../shaders/shader_code.h"

#include "vulkan_instance.h"
#include "vulkan_device_chooser.h"

#include "vulkan_sampler.h"
#include "vulkan_image_view.h"
#include "vulkan_pipeline.h"
#include "vulkan_texture_tuple.h"
#include "vulkan_descriptor_set.h"
#include "vulkan_descriptor_set_layout_binding.h"
#include "vulkan_attachment.h"
#include "vulkan_swap_chain_image.h"

#include "interface/i_vulkan_device.h"

namespace bebone::gfx {
    class VulkanSwapChain;
    class VulkanPipeline;
    class VulkanDescriptorPool;
    class VulkanCommandBufferPool;
    class VulkanCommandBuffer;
    class VulkanShaderModule;
    class VulkanPipelineLayout;
    class VulkanDescriptorSetLayout;
    class VulkanConstRange;
    class VulkanPipelineManager;
    class VulkanRenderTarget;
    class VulkanRenderPass;
    class VulkanFramebuffer;

    class VulkanDevice : public IVulkanDevice, private core::NonCopyable {
        private:
            VulkanInstance& instance_owner;

            VkDevice device;
            VkSurfaceKHR surface;
            VkQueue graphics_queue;
            VkQueue present_queue;

            VkPhysicalDeviceProperties properties;

            // Todo, abstract all things below
            VkPhysicalDevice physical_device = VK_NULL_HANDLE;

            void pick_physical_device(VulkanInstance &instance);
            void create_logical_device();

            // Todo, maybe this can be optimized
            std::unique_ptr<VulkanCommandBufferPool> command_buffer_pool;

        public:
            VulkanDevice(VulkanInstance& instance, std::unique_ptr<Window>& window);
            ~VulkanDevice();

            //  Todo make this a ICommandBufferPool interaface
            // std::unique_ptr<VulkanCommandBuffer> begin_single_time_commands() override;
            // void end_single_time_commands(std::unique_ptr<VulkanCommandBuffer>& command_buffer) override;

            VulkanQueueFamilyIndices find_physical_queue_families() override { return VulkanDeviceChooser::find_queue_families(physical_device, surface); }
            VulkanSwapChainSupportDetails get_swap_chain_support() override { return VulkanDeviceChooser::query_swap_chain_support(physical_device, surface); }

            uint32_t find_memory_type(uint32_t type_filter, VkMemoryPropertyFlags properties) override;
            VkFormat find_supported_format(const std::vector<VkFormat> &candidates, VkImageTiling tiling, VkFormatFeatureFlags features) override;
            VkFormat find_depth_format() override;

            // Vulkan Device
            [[nodiscard]] VkDevice get_vk_device() const override;
            [[nodiscard]] VkSurfaceKHR get_surface() const override;
            [[nodiscard]] VkQueue get_graphics_queue() const override;
            [[nodiscard]] VkQueue get_present_queue() const override;
            void wait_idle() const override;

    };
}

#endif