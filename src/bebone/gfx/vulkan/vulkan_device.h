#ifndef DEVICE_H
#define DEVICE_H

#include "../gfx_backend.h"
#include "../window/window.h"

#include "vulkan_instance.h"
#include "vulkan_physical_device_chooser.h"

#include <iostream>
#include <set>
#include <unordered_set>

namespace bebone::gfx {
    class VulkanDevice : private core::NonCopyable {
        private:
            VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
            bebone::gfx::Window &window;

            VkDevice device_;
            VkSurfaceKHR surface_;

            VkQueue graphicsQueue_;
            VkQueue presentQueue_;

            bebone::gfx::VulkanInstance &vulkanInstance;

            void createSurface(bebone::gfx::VulkanInstance &vulkanInstance);
            void pickPhysicalDevice(bebone::gfx::VulkanInstance &vulkanInstance);
            void createLogicalDevice();

        public:
            VkPhysicalDeviceProperties properties;

            VulkanDevice(bebone::gfx::Window &window, bebone::gfx::VulkanInstance &vulkanInstance);
            ~VulkanDevice();

            VkDevice device() const { return device_; }
            VkSurfaceKHR surface() { return surface_; }
            VkQueue graphicsQueue() { return graphicsQueue_; }
            VkQueue presentQueue() { return presentQueue_; }

            void createImageWithInfo(const VkImageCreateInfo &imageInfo, VkMemoryPropertyFlags properties, VkImage &image, VkDeviceMemory &imageMemory);

            uint32_t findMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties);

            QueueFamilyIndices findPhysicalQueueFamilies() { return VulkanPhysicalDeviceChooser::findQueueFamilies(physicalDevice, surface_); }
            SwapChainSupportDetails getSwapChainSupport() { return VulkanPhysicalDeviceChooser::querySwapChainSupport(physicalDevice, surface_); }

            VkFormat findSupportedFormat(const std::vector<VkFormat> &candidates, VkImageTiling tiling, VkFormatFeatureFlags features);
    };
}

#endif