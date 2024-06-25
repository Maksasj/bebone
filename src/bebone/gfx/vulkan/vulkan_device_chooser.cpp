#include "vulkan_device_chooser.h"

namespace bebone::gfx::vulkan {
    bool VulkanQueueFamilyIndices::is_complete() {
        return graphics_family_has_value && present_family_has_value ;
    }

    const std::vector<const char *> VulkanDeviceChooser::device_extensions = {
        VK_KHR_SWAPCHAIN_EXTENSION_NAME,
        VK_EXT_DESCRIPTOR_INDEXING_EXTENSION_NAME
    };

    bool VulkanDeviceChooser::check_device_extension_support(VkPhysicalDevice device) {
        uint32_t count;
        vkEnumerateDeviceExtensionProperties(device, nullptr, &count, nullptr);

        auto available_extensions = std::vector<VkExtensionProperties> {};
        available_extensions.reserve(count);

        vkEnumerateDeviceExtensionProperties(device, nullptr, &count, available_extensions.data());

        auto required_extensions = std::set<std::string>(device_extensions.begin(), device_extensions.end());

        for (const auto &extension : available_extensions)
            required_extensions.erase(extension.extensionName);

        return required_extensions.empty();
    }

    bool VulkanDeviceChooser::is_device_suitable(VkPhysicalDevice device, VkSurfaceKHR& surface) {
        VulkanQueueFamilyIndices indices = find_queue_families(device, surface);

        bool extensions_supported = check_device_extension_support(device);
        bool swap_chain_adequate = false;

        if (extensions_supported) {
            VulkanSwapChainSupportDetails swap_chain_support = query_swap_chain_support(device, surface);

            swap_chain_adequate = !swap_chain_support.formats.empty() && !swap_chain_support.present_modes.empty();
        }

        VkPhysicalDeviceFeatures supported_features;
        vkGetPhysicalDeviceFeatures(device, &supported_features);

        return indices.is_complete() && extensions_supported && swap_chain_adequate && supported_features.samplerAnisotropy;
    }

    VulkanSwapChainSupportDetails VulkanDeviceChooser::query_swap_chain_support(VkPhysicalDevice device, VkSurfaceKHR& surface) {
        VulkanSwapChainSupportDetails details;
        vkGetPhysicalDeviceSurfaceCapabilitiesKHR(device, surface, &details.capabilities);

        uint32_t format_count;
        vkGetPhysicalDeviceSurfaceFormatsKHR(device, surface, &format_count, nullptr);

        if(format_count != 0) {
            details.formats.resize(format_count);
            vkGetPhysicalDeviceSurfaceFormatsKHR(device, surface, &format_count, details.formats.data());
        }

        uint32_t present_mode_count;
        vkGetPhysicalDeviceSurfacePresentModesKHR(device, surface, &present_mode_count, nullptr);

        if(present_mode_count != 0) {
            details.present_modes.resize(present_mode_count);
            vkGetPhysicalDeviceSurfacePresentModesKHR(device, surface, &present_mode_count, details.present_modes.data());
        }

        return details;
    }

    VulkanQueueFamilyIndices VulkanDeviceChooser::find_queue_families(VkPhysicalDevice device, VkSurfaceKHR& surface) {
        uint32_t queue_family_count = 0;
        vkGetPhysicalDeviceQueueFamilyProperties(device, &queue_family_count, nullptr);

        std::vector<VkQueueFamilyProperties> queue_families(queue_family_count);
        vkGetPhysicalDeviceQueueFamilyProperties(device, &queue_family_count, queue_families.data());

        VulkanQueueFamilyIndices indices;

        int i = 0;
        for(const auto &queue_family : queue_families) {
            if(queue_family.queueCount > 0 && queue_family.queueFlags & VK_QUEUE_GRAPHICS_BIT) {
                indices.graphics_family = i;
                indices.graphics_family_has_value = true;
            }

            VkBool32 present_support = false;
            vkGetPhysicalDeviceSurfaceSupportKHR(device, i, surface, &present_support);

            if(queue_family.queueCount > 0 && present_support) {
                indices.present_family = i;
                indices.present_family_has_value  = true;
            }

            if(indices.is_complete())
                break;

            ++i;
        }

        return indices;
    }

    VkPhysicalDevice VulkanDeviceChooser::get_physical_device(VulkanInstance& instance, VkSurfaceKHR& surface) {
        VkPhysicalDevice physical_device = VK_NULL_HANDLE;

        uint32_t device_count = 0;
        vkEnumeratePhysicalDevices(instance.get_instance(), &device_count, nullptr);
        if (device_count == 0) {
            throw std::runtime_error("failed to find GPUs with Vulkan support!");
        }

        std::cout << "Device count: " << device_count << std::endl;

        auto devices = std::vector<VkPhysicalDevice> {};
        devices.reserve(device_count);
        
        vkEnumeratePhysicalDevices(instance.get_instance(), &device_count, devices.data());

        for(const auto &device : devices) {
            if(is_device_suitable(device, surface)) {
                physical_device = device;
                break;
            }
        }

        if (physical_device == VK_NULL_HANDLE) {
            throw std::runtime_error("failed to find a suitable GPU!");
        }

        return physical_device;
    }
}

