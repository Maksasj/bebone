#ifndef _BEBONE_GFX_VULKAN_SWAP_CHAIN_H_
#define _BEBONE_GFX_VULKAN_SWAP_CHAIN_H_

#include "vulkan_device.h"

#include <string>
#include <vector>
#include <array>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <limits>
#include <set>
#include <stdexcept>

#include "../render_target.h"

namespace bebone::gfx {
    class VulkanResult;
    class VulkanCommandBuffer;

    class VulkanSwapChain : private core::NonCopyable {
        private:
            void create_swap_chain(VulkanDevice& device);
            void create_render_target(VulkanDevice& device);
            void create_sync_objects(VulkanDevice& device);

            static VkSurfaceFormatKHR choose_swap_surface_format(const std::vector<VkSurfaceFormatKHR> &availableFormats);
            static VkPresentModeKHR choose_swap_present_mode(const std::vector<VkPresentModeKHR> &availablePresentModes);
            static VkExtent2D choose_swap_extent(const VkSurfaceCapabilitiesKHR &capabilities, VkExtent2D windowExtent);

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
            // void recreate(VulkanDevice& device, VkExtent2D windowExtent);

            std::unique_ptr<RenderTarget> renderTarget;

            VulkanSwapChain(VulkanDevice &deviceRef, VkExtent2D windowExtent);
            ~VulkanSwapChain();

            VulkanResult acquire_next_image(std::shared_ptr<VulkanDevice>& device, uint32_t *imageIndex);
            VulkanResult submit_command_buffers(std::shared_ptr<VulkanDevice>& device, std::shared_ptr<VulkanCommandBuffer>& commandBuffer, uint32_t *imageIndex);

            size_t currentFrame = 0;
    };
}

#endif