#ifndef DEVICE_H
#define DEVICE_H

#include "../gfx_backend.h"

#include "../window/vulkan_window.h"
#include "vulkan_instance.h"

#include <iostream>
#include <set>
#include <unordered_set>

namespace bebone::gfx {
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

    class VulkanDevice : private core::NonCopyable {
        private:
            VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
            bebone::gfx::VulkanWindow &window;

            VkDevice device_;
            VkSurfaceKHR surface_;

            VkQueue graphicsQueue_;
            VkQueue presentQueue_;

            // const std::vector<const char *> validationLayers = { "VK_LAYER_KHRONOS_validation" };
            const std::vector<const char *> deviceExtensions = {
                    VK_KHR_SWAPCHAIN_EXTENSION_NAME,
                    VK_EXT_DESCRIPTOR_INDEXING_EXTENSION_NAME
            };

            bebone::gfx::VulkanInstance &vulkanInstance;

            void createSurface(bebone::gfx::VulkanInstance &vulkanInstance);
            void pickPhysicalDevice(bebone::gfx::VulkanInstance &vulkanInstance);
            void createLogicalDevice();

            // helper functions
            bool isDeviceSuitable(VkPhysicalDevice device);
            bool checkDeviceExtensionSupport(VkPhysicalDevice device);
            SwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice device);


        public:
            VkPhysicalDeviceProperties properties;

            VulkanDevice(bebone::gfx::VulkanWindow &window, bebone::gfx::VulkanInstance &vulkanInstance);
            ~VulkanDevice();

            VkDevice device() const { return device_; }
            VkSurfaceKHR surface() { return surface_; }
            VkQueue graphicsQueue() { return graphicsQueue_; }
            VkQueue presentQueue() { return presentQueue_; }

            void createImageWithInfo(const VkImageCreateInfo &imageInfo, VkMemoryPropertyFlags properties, VkImage &image, VkDeviceMemory &imageMemory);

            uint32_t findMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties);
            QueueFamilyIndices findPhysicalQueueFamilies() { return findQueueFamilies(physicalDevice); }
            QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device);
            SwapChainSupportDetails getSwapChainSupport() { return querySwapChainSupport(physicalDevice); }
            VkFormat findSupportedFormat(const std::vector<VkFormat> &candidates, VkImageTiling tiling, VkFormatFeatureFlags features);
    };
}

#endif