#ifndef _BEBONE_GFX_SWAP_CHAIN_IMPL_H_
#define _BEBONE_GFX_SWAP_CHAIN_IMPL_H_

#include "device_impl.h"

#include <string>
#include <vector>

#include "render_target.h"

using namespace bebone::gfx;

class MyEngineSwapChainImpl {
	public:
		std::shared_ptr<RenderTarget> renderTarget;

		const size_t FIF;

		MyEngineSwapChainImpl(DeviceImpl &deviceRef, VkExtent2D windowExtent, const size_t& fif);
		~MyEngineSwapChainImpl();

		MyEngineSwapChainImpl(const MyEngineSwapChainImpl &) = delete;
		void operator=(const MyEngineSwapChainImpl &) = delete; 

		VkResult acquireNextImage(uint32_t *imageIndex);
		VkResult submitCommandBuffers(const VkCommandBuffer *buffers, uint32_t *imageIndex);

		size_t currentFrame = 0;
  	private:
		void createSwapChain();
		void createSyncObjects();

		// Helper functions
		static VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR> &availableFormats);
		static VkPresentModeKHR chooseSwapPresentMode(const std::vector<VkPresentModeKHR> &availablePresentModes);
		VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR &capabilities);

		DeviceImpl &device;
		VkExtent2D windowExtent;

		VkSwapchainKHR swapChain;

		std::vector<VkSemaphore> imageAvailableSemaphores;
		std::vector<VkSemaphore> renderFinishedSemaphores;
		std::vector<VkFence> inFlightFences;
		std::vector<VkFence> imagesInFlight;
};

#endif