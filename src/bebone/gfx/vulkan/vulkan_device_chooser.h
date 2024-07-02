#ifndef _BEBONE_GFX_VULKAN_DEVICE_CHOOSER_H_
#define _BEBONE_GFX_VULKAN_DEVICE_CHOOSER_H_

#include <set>

#include "vulkan_instance.h"

namespace bebone::gfx {
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

    class VulkanDeviceChooser {
        private:
            bool check_device_extension_support(VkPhysicalDevice device);
            bool is_device_suitable(VkPhysicalDevice device, VkSurfaceKHR& surface);

        public:
            static const std::vector<const char *> device_extensions;

            static VulkanSwapChainSupportDetails query_swap_chain_support(VkPhysicalDevice device, VkSurfaceKHR& surface);
            static VulkanQueueFamilyIndices find_queue_families(VkPhysicalDevice device, VkSurfaceKHR& surface);

            VkPhysicalDevice get_physical_device(VulkanInstance& instance, VkSurfaceKHR& surface);
    };
}

#endif
