#ifndef _BEBONE_GFX_VULKAN_VULKAN_DEVICE_CHOOSER_H_
#define _BEBONE_GFX_VULKAN_VULKAN_DEVICE_CHOOSER_H_

#include "vulkan_instance.h"

namespace bebone::gfx::vulkan {
    struct SwapChainSupportDetails {
        VkSurfaceCapabilitiesKHR capabilities;
        std::vector<VkSurfaceFormatKHR> formats;
        std::vector<VkPresentModeKHR> presentModes;
    };

    struct QueueFamilyIndices {
        uint32_t graphicsFamily;
        uint32_t presentFamily;
        bool graphicsFamilyHasValue = false;
        bool presentFamilyHasValue = false;
        bool isComplete() { return graphicsFamilyHasValue && presentFamilyHasValue; }
    };

    class VulkanDeviceChooser {
        private:
            bool check_device_extension_support(VkPhysicalDevice device);
            bool is_device_suitable(VkPhysicalDevice device, VkSurfaceKHR& surface);

        public:
            static const std::vector<const char *> deviceExtensions;

            static SwapChainSupportDetails query_swap_chain_support(VkPhysicalDevice device, VkSurfaceKHR& surface);

            static QueueFamilyIndices find_queue_families(VkPhysicalDevice device, VkSurfaceKHR& surface);

            VkPhysicalDevice get_physical_device(VulkanInstance& vulkanInstance, VkSurfaceKHR& surface);
    };
}

#endif
