#include "vulkan_swap_chain.h"

#include "vulkan_result.h"
#include "vulkan_image.h"
#include "vulkan_image_view.h"
#include "vulkan_command_buffer.h"

namespace bebone::gfx {
    VulkanSwapChain::VulkanSwapChain(VulkanDevice& device, VkExtent2D window_extent) : VulkanWrapper<VkSwapchainKHR>(device) {
        auto swap_chain_support = device.get_swap_chain_support();
        extent = choose_swap_extent(swap_chain_support.capabilities, window_extent);

        create_swap_chain(device);

        auto images = create_swap_chain_images(device, surface_format.format);

        // This is default swap chain render pass,
        // but I am not sure is swap chain should manage it own render pass
        render_pass = device.create_render_pass(extent, {
            VulkanAttachmentDesc::color2D(extent, { .format = surface_format.format }),
            VulkanAttachmentDesc::depth2D(extent, { .format = device.find_depth_format() }),
        });

        render_target = device.create_render_target(render_pass, images);

        create_sync_objects(device);
    }

    VulkanSwapChain::~VulkanSwapChain() {
        for (size_t i = 0; i < image_count; i++) {
            vkDestroySemaphore(device.device, render_finished_semaphores[i], nullptr);
            vkDestroySemaphore(device.device, image_available_semaphores[i], nullptr);
            vkDestroyFence(device.device, in_flight_fences[i], nullptr);
        }

        vkDestroySwapchainKHR(device.device, backend, nullptr);
    }

    const size_t& VulkanSwapChain::get_current_frame() const {
        return current_frame;
    }

    const VkExtent2D& VulkanSwapChain::get_extent() const {
        return extent;
    }

    VulkanResult VulkanSwapChain::acquire_next_image(std::shared_ptr<VulkanDevice>& device, uint32_t *image_index) {
        vkWaitForFences(device->device, 1, &in_flight_fences[current_frame], VK_TRUE, std::numeric_limits<uint64_t>::max());

        auto result = vkAcquireNextImageKHR(
            device->device,
            backend,
            std::numeric_limits<uint64_t>::max(),
            image_available_semaphores[current_frame],  // must be a not signaled semaphore
            VK_NULL_HANDLE,
            image_index);

        if(result != VK_SUCCESS && result != VK_SUBOPTIMAL_KHR)
            throw std::runtime_error("failed to acquire swap chain image!");

        return { result };
    }

    VulkanResult VulkanSwapChain::submit_present_command_buffers(
        std::shared_ptr<VulkanDevice>& device,
        std::shared_ptr<VulkanCommandBuffer>& command_buffer,
        uint32_t *image_index
    ) {
        // Submitting and synchronization
        if (images_in_flight[*image_index] != VK_NULL_HANDLE)
            vkWaitForFences(device->device, 1, &images_in_flight[*image_index], VK_TRUE, UINT64_MAX);

        images_in_flight[*image_index] = in_flight_fences[current_frame];

        VkSemaphore wait_semaphores[] = {image_available_semaphores[current_frame]};
        VkPipelineStageFlags wait_stages[] = {VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT};
        VkSemaphore signal_semaphores[] = {render_finished_semaphores[current_frame]};

        VkSubmitInfo submit_info = {};
        submit_info.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
        submit_info.waitSemaphoreCount = 1;
        submit_info.pWaitSemaphores = wait_semaphores;
        submit_info.pWaitDstStageMask = wait_stages;
        submit_info.commandBufferCount = 1;
        submit_info.pCommandBuffers = &command_buffer->backend;
        submit_info.signalSemaphoreCount = 1;
        submit_info.pSignalSemaphores = signal_semaphores;

        vkResetFences(device->device, 1, &in_flight_fences[current_frame]);
        if(vkQueueSubmit(device->graphics_queue, 1, &submit_info, in_flight_fences[current_frame]) != VK_SUCCESS)
            throw std::runtime_error("failed to submit draw command buffer!");

        // Todo, Presenting part
        VkSwapchainKHR swap_chains[] = { backend };

        VkPresentInfoKHR present_info = {};
        present_info.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
        present_info.waitSemaphoreCount = 1;
        present_info.pWaitSemaphores = signal_semaphores;
        present_info.swapchainCount = 1;
        present_info.pSwapchains = swap_chains;
        present_info.pImageIndices = image_index;

        VkResult result = vkQueuePresentKHR(device->present_queue, &present_info);

        current_frame = (current_frame + 1) % image_count;

        if(result != VK_SUCCESS)
            throw std::runtime_error("failed to acquire submit command buffers !");

        return { result };
    }

    std::vector<std::shared_ptr<VulkanSwapChainImageTuple>> VulkanSwapChain::create_swap_chain_images(VulkanDevice& device, VkFormat image_format) {
        uint32_t image_count;

        vkGetSwapchainImagesKHR(device.device, backend, &image_count, nullptr);
        auto images = std::vector<VkImage> {};
        images.resize(image_count);

        auto out = std::vector<std::shared_ptr<VulkanSwapChainImageTuple>> {};
        out.reserve(image_count);

        vkGetSwapchainImagesKHR(device.device, backend, &image_count, images.data());

        for(auto& vk_image : images) {
            auto image = device.create_image(vk_image);
            auto view = device.create_image_view(*image, image_format);

            out.push_back(std::make_shared<VulkanSwapChainImageTuple>(image, view));
        }

        return out;
    }

    void VulkanSwapChain::create_swap_chain(VulkanDevice& device) {
        auto swap_chain_support = device.get_swap_chain_support();

        surface_format = choose_swap_surface_format(swap_chain_support.formats);
        present_mode = choose_swap_present_mode(swap_chain_support.present_modes);

        // Todo image count should be configurable
        image_count = swap_chain_support.capabilities.minImageCount + 1;
        if (swap_chain_support.capabilities.maxImageCount > 0 && image_count > swap_chain_support.capabilities.maxImageCount)
            image_count = swap_chain_support.capabilities.maxImageCount;

        std::cout << "Chosen swap chain image count " << image_count << "\n";

        VkSwapchainCreateInfoKHR create_info = {};
        create_info.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
        create_info.surface = device.surface;
        create_info.minImageCount = image_count;
        create_info.imageFormat = surface_format.format;
        create_info.imageColorSpace = surface_format.colorSpace;
        create_info.imageExtent = extent;
        create_info.imageArrayLayers = 1;
        create_info.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;

        VulkanQueueFamilyIndices indices = device.find_physical_queue_families();
        uint32_t queue_family_indices[] = {indices.graphics_family, indices.present_family};

        if (indices.graphics_family != indices.present_family) {
            create_info.imageSharingMode = VK_SHARING_MODE_CONCURRENT;
            create_info.queueFamilyIndexCount = 2;
            create_info.pQueueFamilyIndices = queue_family_indices;
        } else {
            create_info.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
            create_info.queueFamilyIndexCount = 0;      // Optional
            create_info.pQueueFamilyIndices = nullptr;  // Optional
        }

        create_info.preTransform = swap_chain_support.capabilities.currentTransform;
        create_info.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
        create_info.presentMode = present_mode;
        create_info.clipped = VK_TRUE;
        create_info.oldSwapchain = VK_NULL_HANDLE;

        if(vkCreateSwapchainKHR(device.device, &create_info, nullptr, &backend) != VK_SUCCESS)
            throw std::runtime_error("failed to create swap chain!");
    }

    void VulkanSwapChain::create_sync_objects(VulkanDevice& device) {
        image_available_semaphores.resize(image_count);
        render_finished_semaphores.resize(image_count);
        in_flight_fences.resize(image_count);
        images_in_flight.resize(image_count, VK_NULL_HANDLE);

        VkSemaphoreCreateInfo semaphore_info = {};
        semaphore_info.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;

        VkFenceCreateInfo fence_info = {};
        fence_info.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
        fence_info.flags = VK_FENCE_CREATE_SIGNALED_BIT;

        for (size_t i = 0; i < image_count; i++) {
            if(vkCreateSemaphore(device.device, &semaphore_info, nullptr, &image_available_semaphores[i]) != VK_SUCCESS)
                throw std::runtime_error("failed to create synchronization objects for a frame!");

            if(vkCreateSemaphore(device.device, &semaphore_info, nullptr, &render_finished_semaphores[i]) != VK_SUCCESS)
                throw std::runtime_error("failed to create synchronization objects for a frame!");

            if (vkCreateFence(device.device, &fence_info, nullptr, &in_flight_fences[i]) != VK_SUCCESS)
                throw std::runtime_error("failed to create synchronization objects for a frame!");
        }
    }

    VkSurfaceFormatKHR VulkanSwapChain::choose_swap_surface_format(const std::vector<VkSurfaceFormatKHR> &available_formats) {
        for (const auto &available_format : available_formats)
            if (available_format.format == VK_FORMAT_B8G8R8A8_UNORM && available_format.colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR)
                return available_format;

        return available_formats[0];
    }

    VkPresentModeKHR VulkanSwapChain::choose_swap_present_mode(const std::vector<VkPresentModeKHR> &available_present_modes) {
        for (const auto &available_present_mode : available_present_modes) {
            if (available_present_mode == VK_PRESENT_MODE_MAILBOX_KHR) {
                std::cout << "Present mode: Mailbox" << std::endl;
                return available_present_mode;
            }
        }

        std::cout << "Present mode: V-Sync" << std::endl;

        return VK_PRESENT_MODE_FIFO_KHR;
    }

    VkExtent2D VulkanSwapChain::choose_swap_extent(const VkSurfaceCapabilitiesKHR &capabilities, VkExtent2D window_extent) {
        if (capabilities.currentExtent.width != std::numeric_limits<uint32_t>::max()) {
            return capabilities.currentExtent;
        } else {
            VkExtent2D actual_extent = window_extent;

            actual_extent.width = std::max(
                capabilities.minImageExtent.width,
                std::min(capabilities.maxImageExtent.width, actual_extent.width)); // Todo
            actual_extent.height = std::max(
                capabilities.minImageExtent.height,
                std::min(capabilities.maxImageExtent.height, actual_extent.height)); // Todo

            return actual_extent;
        }
    }
}
