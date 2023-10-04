#ifndef DEVICE_H
#define DEVICE_H

#include "gfx_backend.h"

#include "window/window.h"
#include "vulkan/vulkan_instance.h"

#include <iostream>
#include <set>
#include <unordered_set>

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

namespace bebone::gfx {
    class VulkanDevice {
    private:
        VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
        bebone::gfx::Window &window;

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

        QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device);

        bool checkDeviceExtensionSupport(VkPhysicalDevice device);

        SwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice device);

    public:
        VkPhysicalDeviceProperties properties;

        VulkanDevice(bebone::gfx::Window &window, bebone::gfx::VulkanInstance &vulkanInstance);

        ~VulkanDevice();

        VulkanDevice(const VulkanDevice &) = delete;

        void operator=(const VulkanDevice &) = delete;

        VulkanDevice(VulkanDevice &&) = delete;

        VulkanDevice &operator=(VulkanDevice &&) = delete;

        VkDevice device() const { return device_; }

        VkSurfaceKHR surface() { return surface_; }

        VkQueue graphicsQueue() { return graphicsQueue_; }

        VkQueue presentQueue() { return presentQueue_; }

        SwapChainSupportDetails getSwapChainSupport() { return querySwapChainSupport(physicalDevice); }

        uint32_t findMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties);

        QueueFamilyIndices findPhysicalQueueFamilies() { return findQueueFamilies(physicalDevice); }

        VkFormat findSupportedFormat(const std::vector<VkFormat> &candidates, VkImageTiling tiling,
                                     VkFormatFeatureFlags features);

        void createImageWithInfo(const VkImageCreateInfo &imageInfo, VkMemoryPropertyFlags properties, VkImage &image,
                                 VkDeviceMemory &imageMemory);
    };
}

#endif