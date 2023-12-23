#ifndef _BEBONE_GFX_VULKAN_SWAP_CHAIN_H_
#define _BEBONE_GFX_VULKAN_SWAP_CHAIN_H_

#include "vulkan_device.h"

#include <string>
#include <vector>

#include "../render_target.h"

namespace bebone::gfx {
    class VulkanResult;
    class VulkanCommandBuffer;

    class VulkanSwapChain : private core::NonCopyable {
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

            u32 imageCount;

            std::vector<VkSemaphore> imageAvailableSemaphores;
            std::vector<VkSemaphore> renderFinishedSemaphores;
            std::vector<VkFence> inFlightFences;
            std::vector<VkFence> imagesInFlight;
        public:
            void recreate(VkExtent2D windowExtent);

            std::unique_ptr<RenderTarget> renderTarget;

            VulkanSwapChain(VulkanDevice &deviceRef, VkExtent2D windowExtent);
            ~VulkanSwapChain();

            VulkanResult acquire_next_image(uint32_t *imageIndex);
            VulkanResult submit_command_buffers(std::shared_ptr<VulkanCommandBuffer>& commandBuffer, uint32_t *imageIndex);

            const u32& get_image_count() const {
                return imageCount;
            }

            size_t currentFrame = 0;
    };
}

#endif