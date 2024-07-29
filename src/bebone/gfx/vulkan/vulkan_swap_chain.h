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

namespace bebone::gfx {
    class VulkanResult;
    class VulkanCommandBuffer;

    class VulkanSwapChain : public VulkanWrapper<VkSwapchainKHR>, private core::NonCopyable {
        protected:
            VkExtent2D extent;

            VkSurfaceFormatKHR surface_format;
            VkPresentModeKHR present_mode;

            size_t current_frame = 0;
            u32 image_count; // Todo this should be removed

            std::vector<VkSemaphore> image_available_semaphores;
            std::vector<VkSemaphore> render_finished_semaphores;
            std::vector<VkFence> in_flight_fences;
            std::vector<VkFence> images_in_flight;

            static VkSurfaceFormatKHR choose_swap_surface_format(const std::vector<VkSurfaceFormatKHR> &available_formats);
            static VkPresentModeKHR choose_swap_present_mode(const std::vector<VkPresentModeKHR> &available_present_modes);
            static VkExtent2D choose_swap_extent(const VkSurfaceCapabilitiesKHR &capabilities, VkExtent2D window_extent);

            void create_swap_chain(VulkanDevice& device);
            void create_sync_objects(VulkanDevice& device);

            std::vector<std::shared_ptr<VulkanSwapChainImageTuple>> create_swap_chain_images(VulkanDevice& device, VkFormat image_format);

    public:
            VulkanSwapChain(VulkanDevice& device, VkExtent2D window_extent);

            const size_t& get_current_frame() const;
            const VkExtent2D& get_extent() const;

            std::shared_ptr<VulkanRenderPass> render_pass;
            std::shared_ptr<VulkanRenderTarget> render_target;

            VulkanResult acquire_next_image(
                std::shared_ptr<VulkanDevice>& device,
                uint32_t *image_index);

            VulkanResult submit_present_command_buffers(
                std::shared_ptr<VulkanDevice>& device,
                std::shared_ptr<VulkanCommandBuffer>& command_buffer,
                uint32_t *image_index);

            void destroy(VulkanDevice& device) override;
    };
}

#endif