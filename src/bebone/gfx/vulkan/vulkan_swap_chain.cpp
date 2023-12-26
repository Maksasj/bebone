#include "vulkan_swap_chain.h"

#include "vulkan_result.h"
#include "vulkan_image.h"
#include "vulkan_image_view.h"
#include "vulkan_command_buffer.h"

namespace bebone::gfx {
    VulkanSwapChain::VulkanSwapChain(VulkanDevice &device, VkExtent2D _windowExtent) {
        SwapChainSupportDetails swapChainSupport = device.get_swap_chain_support();
        extent = choose_swap_extent(swapChainSupport.capabilities, _windowExtent);

        create_swap_chain(device);

        auto images = create_swap_chain_images(device, surfaceFormat.format);
        renderTarget = std::make_unique<RenderTarget>(device, images, surfaceFormat.format, extent);

        create_sync_objects(device);
    }

    VulkanResult VulkanSwapChain::acquire_next_image(std::shared_ptr<VulkanDevice>& device, uint32_t *imageIndex) {
        vkWaitForFences(device->device(), 1, &inFlightFences[currentFrame], VK_TRUE, std::numeric_limits<uint64_t>::max());

        auto result = vkAcquireNextImageKHR(
                device->device(),
                backend,
                std::numeric_limits<uint64_t>::max(),
                imageAvailableSemaphores[currentFrame],  // must be a not signaled semaphore
                VK_NULL_HANDLE,
                imageIndex);

        if(result != VK_SUCCESS && result != VK_SUBOPTIMAL_KHR)
            throw std::runtime_error("failed to acquire swap chain image!");

        return VulkanResult(result);
    }

    VulkanResult VulkanSwapChain::submit_command_buffers(std::shared_ptr<VulkanDevice>& device, std::shared_ptr<VulkanCommandBuffer>& commandBuffer, uint32_t *imageIndex) {
        // Submitting and synchronization
        if (imagesInFlight[*imageIndex] != VK_NULL_HANDLE) {
            vkWaitForFences(device->device(), 1, &imagesInFlight[*imageIndex], VK_TRUE, UINT64_MAX);
        }

        imagesInFlight[*imageIndex] = inFlightFences[currentFrame];

        VkSemaphore waitSemaphores[] = {imageAvailableSemaphores[currentFrame]};
        VkPipelineStageFlags waitStages[] = {VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT};
        VkSemaphore signalSemaphores[] = {renderFinishedSemaphores[currentFrame]};

        VkSubmitInfo submitInfo = {};

        submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
        submitInfo.waitSemaphoreCount = 1;
        submitInfo.pWaitSemaphores = waitSemaphores;
        submitInfo.pWaitDstStageMask = waitStages;
        submitInfo.commandBufferCount = 1;
        submitInfo.pCommandBuffers = &commandBuffer->backend;
        submitInfo.signalSemaphoreCount = 1;
        submitInfo.pSignalSemaphores = signalSemaphores;

        vkResetFences(device->device(), 1, &inFlightFences[currentFrame]);
        if (vkQueueSubmit(device->graphicsQueue(), 1, &submitInfo, inFlightFences[currentFrame]) != VK_SUCCESS) {
            throw std::runtime_error("failed to submit draw command buffer!");
        }

        // Presenting part
        VkSwapchainKHR swapChains[] = { backend };

        VkPresentInfoKHR presentInfo = {};
        presentInfo.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
        presentInfo.waitSemaphoreCount = 1;
        presentInfo.pWaitSemaphores = signalSemaphores;
        presentInfo.swapchainCount = 1;
        presentInfo.pSwapchains = swapChains;
        presentInfo.pImageIndices = imageIndex;

        VkResult result = vkQueuePresentKHR(device->presentQueue(), &presentInfo);

        currentFrame = (currentFrame + 1) % imageCount;

        if(result != VK_SUCCESS) {
            throw std::runtime_error("failed to acquire submit command buffers !");
        }

        return { result };
    }

    std::vector<VulkanSwapChainImageTuple> VulkanSwapChain::create_swap_chain_images(VulkanDevice& device, VkFormat imageFormat) {
        std::vector<VkImage> images;
        uint32_t imageCount;

        vkGetSwapchainImagesKHR(device.device(), backend, &imageCount, nullptr);
        images.resize(imageCount);
        vkGetSwapchainImagesKHR(device.device(), backend, &imageCount, images.data());

        std::vector<VulkanSwapChainImageTuple> out;

        for(auto& image : images) {
            VulkanSwapChainImageTuple swapChainImage;

            swapChainImage.image = std::make_shared<VulkanImage>(image);
            swapChainImage.view = std::make_shared<VulkanImageView>(device, *swapChainImage.image, imageFormat);

            out.push_back(swapChainImage);
        }

        return out;
    }

    void VulkanSwapChain::create_swap_chain(VulkanDevice& device) {
        SwapChainSupportDetails swapChainSupport = device.get_swap_chain_support();

        surfaceFormat = choose_swap_surface_format(swapChainSupport.formats);
        presentMode = choose_swap_present_mode(swapChainSupport.presentModes);

        // Todo image count should be configurable
        imageCount = swapChainSupport.capabilities.minImageCount + 1;
        if (swapChainSupport.capabilities.maxImageCount > 0 && imageCount > swapChainSupport.capabilities.maxImageCount) {
            imageCount = swapChainSupport.capabilities.maxImageCount;
        }

        std::cout << "Chosen swap chain image count " << imageCount << "\n";

        VkSwapchainCreateInfoKHR createInfo = {};
        createInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
        createInfo.surface = device.surface();

        createInfo.minImageCount = imageCount;
        createInfo.imageFormat = surfaceFormat.format;
        createInfo.imageColorSpace = surfaceFormat.colorSpace;
        createInfo.imageExtent = extent;
        createInfo.imageArrayLayers = 1;
        createInfo.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;

        QueueFamilyIndices indices = device.findPhysicalQueueFamilies();
        uint32_t queueFamilyIndices[] = {indices.graphicsFamily, indices.presentFamily};

        if (indices.graphicsFamily != indices.presentFamily) {
            createInfo.imageSharingMode = VK_SHARING_MODE_CONCURRENT;
            createInfo.queueFamilyIndexCount = 2;
            createInfo.pQueueFamilyIndices = queueFamilyIndices;
        } else {
            createInfo.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
            createInfo.queueFamilyIndexCount = 0;      // Optional
            createInfo.pQueueFamilyIndices = nullptr;  // Optional
        }

        createInfo.preTransform = swapChainSupport.capabilities.currentTransform;
        createInfo.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;

        createInfo.presentMode = presentMode;
        createInfo.clipped = VK_TRUE;

        createInfo.oldSwapchain = VK_NULL_HANDLE;

        if (vkCreateSwapchainKHR(device.device(), &createInfo, nullptr, &backend) != VK_SUCCESS) {
            throw std::runtime_error("failed to create swap chain!");
        }
    }

    void VulkanSwapChain::create_sync_objects(VulkanDevice& device) {
        imageAvailableSemaphores.resize(imageCount);
        renderFinishedSemaphores.resize(imageCount);
        inFlightFences.resize(imageCount);
        imagesInFlight.resize(renderTarget->swapChainImages.size(), VK_NULL_HANDLE);

        VkSemaphoreCreateInfo semaphoreInfo = {};
        semaphoreInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;

        VkFenceCreateInfo fenceInfo = {};
        fenceInfo.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
        fenceInfo.flags = VK_FENCE_CREATE_SIGNALED_BIT;

        for (size_t i = 0; i < imageCount; i++) {
            if(vkCreateSemaphore(device.device(), &semaphoreInfo, nullptr, &imageAvailableSemaphores[i]) != VK_SUCCESS) {
                throw std::runtime_error("failed to create synchronization objects for a frame!");
            }

            if(vkCreateSemaphore(device.device(), &semaphoreInfo, nullptr, &renderFinishedSemaphores[i]) != VK_SUCCESS) {
                throw std::runtime_error("failed to create synchronization objects for a frame!");
            }

            if (vkCreateFence(device.device(), &fenceInfo, nullptr, &inFlightFences[i]) != VK_SUCCESS) {
                throw std::runtime_error("failed to create synchronization objects for a frame!");
            }
        }
    }

    VkSurfaceFormatKHR VulkanSwapChain::choose_swap_surface_format(const std::vector<VkSurfaceFormatKHR> &availableFormats) {
        for (const auto &availableFormat : availableFormats) {
            if (availableFormat.format == VK_FORMAT_B8G8R8A8_UNORM && availableFormat.colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR) {
                return availableFormat;
            }
        }

        return availableFormats[0];
    }

    VkPresentModeKHR VulkanSwapChain::choose_swap_present_mode(const std::vector<VkPresentModeKHR> &availablePresentModes) {
        for (const auto &availablePresentMode : availablePresentModes) {
            if (availablePresentMode == VK_PRESENT_MODE_MAILBOX_KHR) {
                std::cout << "Present mode: Mailbox" << std::endl;
                return availablePresentMode;
            }
        }

        std::cout << "Present mode: V-Sync" << std::endl;

        return VK_PRESENT_MODE_FIFO_KHR;
    }

    VkExtent2D VulkanSwapChain::choose_swap_extent(const VkSurfaceCapabilitiesKHR &capabilities, VkExtent2D _windowExtent) {
        if (capabilities.currentExtent.width != std::numeric_limits<uint32_t>::max()) {
            return capabilities.currentExtent;
        } else {
            VkExtent2D actualExtent = _windowExtent;

            actualExtent.width = std::max(
                capabilities.minImageExtent.width,
                std::min(capabilities.maxImageExtent.width, actualExtent.width));
            actualExtent.height = std::max(
                capabilities.minImageExtent.height,
                std::min(capabilities.maxImageExtent.height, actualExtent.height));

            return actualExtent;
        }
    }

    void VulkanSwapChain::destroy(VulkanDevice& device) {
        renderTarget->destroy(device);

        // Todo move this somewhere else
        for (size_t i = 0; i < imageCount; i++) {
            vkDestroySemaphore(device.device(), renderFinishedSemaphores[i], nullptr);
            vkDestroySemaphore(device.device(), imageAvailableSemaphores[i], nullptr);
            vkDestroyFence(device.device(), inFlightFences[i], nullptr);
        }

        vkDestroySwapchainKHR(device.device(), backend, nullptr);
    }
}
