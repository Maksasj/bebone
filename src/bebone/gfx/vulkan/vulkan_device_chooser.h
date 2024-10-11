#ifndef _BEBONE_GFX_VULKAN_DEVICE_CHOOSER_H_
#define _BEBONE_GFX_VULKAN_DEVICE_CHOOSER_H_

#include <set>

#include "vulkan_instance.h"

#include "interface/i_vulkan_device.h"

namespace bebone::gfx {
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
