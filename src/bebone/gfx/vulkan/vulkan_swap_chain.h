#ifndef _BEBONE_GFX_VULKAN_SWAP_CHAIN_H_
#define _BEBONE_GFX_VULKAN_SWAP_CHAIN_H_

#include "vulkan_device.h"

#include <string>
#include <vector>

#include "../render_target.h"

namespace bebone::gfx {
    class VulkanSwapChain {
        private:
            void createSwapChain();
            void createRenderTarget();
            void createSyncObjects();

            // Helper functions
            static VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR> &availableFormats);
            static VkPresentModeKHR chooseSwapPresentMode(const std::vector<VkPresentModeKHR> &availablePresentModes);
            static VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR &capabilities, VkExtent2D windowExtent);

            VulkanDevice &device;

            VkExtent2D extent;
            VkSurfaceFormatKHR surfaceFormat;
            VkPresentModeKHR presentMode;

            VkSwapchainKHR swapChain;

            std::vector<VkSemaphore> imageAvailableSemaphores;
            std::vector<VkSemaphore> renderFinishedSemaphores;
            std::vector<VkFence> inFlightFences;
            std::vector<VkFence> imagesInFlight;
        public:
            void recreate(VkExtent2D windowExtent);

            std::unique_ptr<RenderTarget> renderTarget;

            const size_t FIF;

            VulkanSwapChain(VulkanDevice &deviceRef, VkExtent2D windowExtent, const size_t& fif);
            ~VulkanSwapChain();

            VulkanSwapChain(const VulkanSwapChain &) = delete;
            void operator=(const VulkanSwapChain &) = delete;

            VkResult acquireNextImage(uint32_t *imageIndex);
            VkResult submitCommandBuffers(const VkCommandBuffer *buffers, uint32_t *imageIndex);

            size_t currentFrame = 0;
    };
}

#endif