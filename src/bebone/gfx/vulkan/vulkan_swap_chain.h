#ifndef _BEBONE_GFX_VULKAN_SWAP_CHAIN_H_
#define _BEBONE_GFX_VULKAN_SWAP_CHAIN_H_

#include <string>
#include <vector>
#include <array>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <limits>
#include <set>
#include <stdexcept>
#include <numeric>

#include "vulkan_device.h"
#include "vulkan_render_target.h"
#include "vulkan_wrapper.tpp"

namespace bebone::gfx::vulkan {
    class VulkanResult;
    class VulkanCommandBuffer;

    // struct VulkanSwapChainImageTuple; // Todo redefenition

    class VulkanSwapChain : public VulkanWrapper<VkSwapchainKHR>, private core::NonCopyable {
        public:
            void create_swap_chain(VulkanDevice& device);
            void create_sync_objects(VulkanDevice& device);

            static VkSurfaceFormatKHR choose_swap_surface_format(const std::vector<VkSurfaceFormatKHR> &availableFormats);
            static VkPresentModeKHR choose_swap_present_mode(const std::vector<VkPresentModeKHR> &availablePresentModes);
            static VkExtent2D choose_swap_extent(const VkSurfaceCapabilitiesKHR &capabilities, VkExtent2D windowExtent);

            VkExtent2D extent;
            VkSurfaceFormatKHR surfaceFormat;
            VkPresentModeKHR presentMode;

            u32 imageCount;

            std::vector<VkSemaphore> imageAvailableSemaphores;
            std::vector<VkSemaphore> renderFinishedSemaphores;
            std::vector<VkFence> inFlightFences;
            std::vector<VkFence> imagesInFlight;

            std::shared_ptr<VulkanRenderTarget> render_target;

            VulkanSwapChain(VulkanDevice& device, VkExtent2D windowExtent);

            std::vector<VulkanSwapChainImageTuple> create_swap_chain_images(VulkanDevice& device, VkFormat image_format);

            VulkanResult acquire_next_image(std::shared_ptr<VulkanDevice>& device, uint32_t *imageIndex);
            VulkanResult submit_command_buffers(std::shared_ptr<VulkanDevice>& device, std::shared_ptr<VulkanCommandBuffer>& command_buffer, uint32_t *imageIndex);

            size_t currentFrame = 0;

            void destroy(VulkanDevice& device) override;
    };
}

#endif