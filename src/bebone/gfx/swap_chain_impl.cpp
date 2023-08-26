#include "swap_chain_impl.h"

// std
#include <array>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <limits>
#include <set>
#include <stdexcept>

MyEngineSwapChainImpl::MyEngineSwapChainImpl(DeviceImpl &deviceRef, VkExtent2D _windowExtent, const size_t& fif) 
	: FIF(fif), device{deviceRef}, windowExtent{_windowExtent} {
	
	createSwapChain();
	createSyncObjects();
}

MyEngineSwapChainImpl::~MyEngineSwapChainImpl() {
	if (swapChain != nullptr) {
		vkDestroySwapchainKHR(device.device(), swapChain, nullptr);
		swapChain = nullptr;
	}

	// // cleanup synchronization objects
	for (size_t i = 0; i < FIF; i++) {
		vkDestroySemaphore(device.device(), renderFinishedSemaphores[i], nullptr);
		vkDestroySemaphore(device.device(), imageAvailableSemaphores[i], nullptr);
		vkDestroyFence(device.device(), inFlightFences[i], nullptr);
	}
}

VkResult MyEngineSwapChainImpl::acquireNextImage(uint32_t *imageIndex) {
	vkWaitForFences(device.device(), 1, &inFlightFences[currentFrame], VK_TRUE, std::numeric_limits<uint64_t>::max());

	VkResult result = vkAcquireNextImageKHR(
		device.device(),
		swapChain,
		std::numeric_limits<uint64_t>::max(),
		imageAvailableSemaphores[currentFrame],  // must be a not signaled semaphore
		VK_NULL_HANDLE,
		imageIndex);

  return result;
}

VkResult MyEngineSwapChainImpl::submitCommandBuffers(const VkCommandBuffer *buffers, uint32_t *imageIndex) {
	if (imagesInFlight[*imageIndex] != VK_NULL_HANDLE) {
		vkWaitForFences(device.device(), 1, &imagesInFlight[*imageIndex], VK_TRUE, UINT64_MAX);
	}
	
	imagesInFlight[*imageIndex] = inFlightFences[currentFrame];

	VkSubmitInfo submitInfo = {};
	submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;

	VkSemaphore waitSemaphores[] = {imageAvailableSemaphores[currentFrame]};
	VkPipelineStageFlags waitStages[] = {VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT};
	submitInfo.waitSemaphoreCount = 1;
	submitInfo.pWaitSemaphores = waitSemaphores;
	submitInfo.pWaitDstStageMask = waitStages;

	submitInfo.commandBufferCount = 1;
	submitInfo.pCommandBuffers = buffers;

	VkSemaphore signalSemaphores[] = {renderFinishedSemaphores[currentFrame]};
	submitInfo.signalSemaphoreCount = 1;
	submitInfo.pSignalSemaphores = signalSemaphores;

	vkResetFences(device.device(), 1, &inFlightFences[currentFrame]);
	if (vkQueueSubmit(device.graphicsQueue(), 1, &submitInfo, inFlightFences[currentFrame]) != VK_SUCCESS) {
		throw std::runtime_error("failed to submit draw command buffer!");
	}

	VkPresentInfoKHR presentInfo = {};
	presentInfo.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;

	presentInfo.waitSemaphoreCount = 1;
	presentInfo.pWaitSemaphores = signalSemaphores;

	VkSwapchainKHR swapChains[] = {swapChain};
	presentInfo.swapchainCount = 1;
	presentInfo.pSwapchains = swapChains;

	presentInfo.pImageIndices = imageIndex;

	VkResult result = vkQueuePresentKHR(device.presentQueue(), &presentInfo);

	currentFrame = (currentFrame + 1) % FIF;

	return result;
}

void MyEngineSwapChainImpl::createSwapChain() {
	SwapChainSupportDetails swapChainSupport = device.getSwapChainSupport();

	VkSurfaceFormatKHR surfaceFormat = chooseSwapSurfaceFormat(swapChainSupport.formats);
	VkPresentModeKHR presentMode = chooseSwapPresentMode(swapChainSupport.presentModes);
	VkExtent2D extent = chooseSwapExtent(swapChainSupport.capabilities);

	// uint32_t imageCount = swapChainSupport.capabilities.minImageCount + 1;
	uint32_t imageCount = 2; // Todo this is a fif

	// if (swapChainSupport.capabilities.maxImageCount > 0 && imageCount > swapChainSupport.capabilities.maxImageCount) {
	// 	imageCount = swapChainSupport.capabilities.maxImageCount;
	// }

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

	if (vkCreateSwapchainKHR(device.device(), &createInfo, nullptr, &swapChain) != VK_SUCCESS) {
		throw std::runtime_error("failed to create swap chain!");
	}


	std::vector<VkImage> swapChainImages;

	// we only specified a minimum number of images in the swap chain, so the implementation is
	// allowed to create a swap chain with more. That's why we'll first query the final number of
	// images with vkGetSwapchainImagesKHR, then resize the container and finally call it again to
	// retrieve the handles.
	vkGetSwapchainImagesKHR(device.device(), swapChain, &imageCount, nullptr);
	swapChainImages.resize(imageCount);
	vkGetSwapchainImagesKHR(device.device(), swapChain, &imageCount, swapChainImages.data());

	renderTarget = std::make_shared<RenderTarget>(device, swapChainImages, surfaceFormat.format, extent);
}

void MyEngineSwapChainImpl::createSyncObjects() {
	imageAvailableSemaphores.resize(FIF);
	renderFinishedSemaphores.resize(FIF);
	inFlightFences.resize(FIF);
	imagesInFlight.resize(renderTarget->swapChainImages.size(), VK_NULL_HANDLE);

	VkSemaphoreCreateInfo semaphoreInfo = {};
	semaphoreInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;

	VkFenceCreateInfo fenceInfo = {};
	fenceInfo.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
	fenceInfo.flags = VK_FENCE_CREATE_SIGNALED_BIT;

	for (size_t i = 0; i < FIF; i++) {
		if (vkCreateSemaphore(device.device(), &semaphoreInfo, nullptr, &imageAvailableSemaphores[i]) !=
				VK_SUCCESS ||
			vkCreateSemaphore(device.device(), &semaphoreInfo, nullptr, &renderFinishedSemaphores[i]) !=
				VK_SUCCESS ||
			vkCreateFence(device.device(), &fenceInfo, nullptr, &inFlightFences[i]) != VK_SUCCESS) {
		throw std::runtime_error("failed to create synchronization objects for a frame!");
		}
	}
}

VkSurfaceFormatKHR MyEngineSwapChainImpl::chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR> &availableFormats) {
	for (const auto &availableFormat : availableFormats) {
		if (availableFormat.format == VK_FORMAT_B8G8R8A8_UNORM && availableFormat.colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR) {
			return availableFormat;
		}
	}

	return availableFormats[0];
}

VkPresentModeKHR MyEngineSwapChainImpl::chooseSwapPresentMode(const std::vector<VkPresentModeKHR> &availablePresentModes) {
	for (const auto &availablePresentMode : availablePresentModes) {
		if (availablePresentMode == VK_PRESENT_MODE_MAILBOX_KHR) {
			std::cout << "Present mode: Mailbox" << std::endl;
			return availablePresentMode;
		}
	}

	// for (const auto &availablePresentMode : availablePresentModes) {
	//   if (availablePresentMode == VK_PRESENT_MODE_IMMEDIATE_KHR) {
	//     std::cout << "Present mode: Immediate" << std::endl;
	//     return availablePresentMode;
	//   }
	// }

	std::cout << "Present mode: V-Sync" << std::endl;
	return VK_PRESENT_MODE_FIFO_KHR;
}

VkExtent2D MyEngineSwapChainImpl::chooseSwapExtent(const VkSurfaceCapabilitiesKHR &capabilities) {
	if (capabilities.currentExtent.width != std::numeric_limits<uint32_t>::max()) {
		return capabilities.currentExtent;
	} else {
		VkExtent2D actualExtent = windowExtent;
		actualExtent.width = std::max(
			capabilities.minImageExtent.width,
			std::min(capabilities.maxImageExtent.width, actualExtent.width));
		actualExtent.height = std::max(
			capabilities.minImageExtent.height,
			std::min(capabilities.maxImageExtent.height, actualExtent.height));

		return actualExtent;
	}
}

