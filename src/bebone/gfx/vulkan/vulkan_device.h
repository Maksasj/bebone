#ifndef DEVICE_H
#define DEVICE_H

#include "../gfx_backend.h"
#include "../window/window.h"

#include "vulkan_instance.h"
#include "vulkan_device_chooser.h"
#include "vulkan_buffer_impl.h"

#include <iostream>
#include <set>
#include <unordered_set>

namespace bebone::gfx {
    class VulkanSwapChain;

    class VulkanDevice : private core::NonCopyable {
        private:
            VulkanWindow &window;

            VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;

            VkDevice device_;
            VkSurfaceKHR surface_;

            VkQueue graphicsQueue_;
            VkQueue presentQueue_;

            VulkanInstance &vulkanInstance;

            void createSurface(VulkanInstance &vulkanInstance);
            void pickPhysicalDevice(VulkanInstance &vulkanInstance);
            void createLogicalDevice();

        public:
            VkPhysicalDeviceProperties properties;

            VulkanDevice(VulkanWindow &window, VulkanInstance &vulkanInstance);
            ~VulkanDevice();

            std::shared_ptr<VulkanBufferImpl> create_buffer(const size_t& size);

            std::shared_ptr<VulkanSwapChain> create_swapchain(VulkanWindow& window);

            VkDevice device() const { return device_; }
            VkSurfaceKHR surface() { return surface_; }
            VkQueue graphicsQueue() { return graphicsQueue_; }
            VkQueue presentQueue() { return presentQueue_; }

            void createImageWithInfo(const VkImageCreateInfo &imageInfo, VkMemoryPropertyFlags properties, VkImage &image, VkDeviceMemory &imageMemory);

            uint32_t findMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties);

            QueueFamilyIndices findPhysicalQueueFamilies() { return VulkanDeviceChooser::findQueueFamilies(physicalDevice, surface_); }
            SwapChainSupportDetails getSwapChainSupport() { return VulkanDeviceChooser::querySwapChainSupport(physicalDevice, surface_); }

            VkFormat findSupportedFormat(const std::vector<VkFormat> &candidates, VkImageTiling tiling, VkFormatFeatureFlags features);
        };
}

#endif