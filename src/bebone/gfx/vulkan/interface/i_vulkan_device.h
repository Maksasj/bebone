#ifndef _BEBONE_GFX_I_VULKAN_DEVICE_H_
#define _BEBONE_GFX_I_VULKAN_DEVICE_H_

#include "../../gfx_backend.h"

#include "i_vulkan_command_buffer.h"

namespace bebone::gfx {
    using namespace bebone::core;

    struct VulkanSwapChainSupportDetails {
        VkSurfaceCapabilitiesKHR capabilities;
        std::vector<VkSurfaceFormatKHR> formats;
        std::vector<VkPresentModeKHR> present_modes;
    };

    struct VulkanQueueFamilyIndices {
        uint32_t graphics_family;
        uint32_t present_family;
        bool graphics_family_has_value = false;
        bool present_family_has_value  = false;

        bool is_complete();
    };

    class IVulkanDevice {
        public:
            virtual uint32_t find_memory_type(uint32_t type_filter, VkMemoryPropertyFlags properties) = 0;
            virtual VkFormat find_supported_format(const std::vector<VkFormat> &candidates, VkImageTiling tiling, VkFormatFeatureFlags features) = 0;
            virtual VkFormat find_depth_format() = 0;

            // virtual std::unique_ptr<IVulkanCommandBuffer> begin_single_time_commands() = 0;
            // virtual void end_single_time_commands(std::unique_ptr<IVulkanCommandBuffer>& command_buffer) = 0;

            virtual VulkanQueueFamilyIndices find_physical_queue_families() = 0;
            virtual VulkanSwapChainSupportDetails get_swap_chain_support() = 0;

            [[nodiscard]] virtual VkDevice get_vk_device() const = 0;
            [[nodiscard]] virtual VkSurfaceKHR get_surface() const = 0;
            [[nodiscard]] virtual VkQueue get_graphics_queue() const = 0;
            [[nodiscard]] virtual VkQueue get_present_queue() const = 0;
            virtual void wait_idle() const = 0;
    };
}

#endif
