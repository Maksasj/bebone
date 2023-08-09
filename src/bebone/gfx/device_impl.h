#ifndef DEVICE_H
#define DEVICE_H

#include "gfx_backend.h"

#include "window/window.h"
// std lib headers
#include <string>
#include <vector>

struct SwapChainSupportDetails {
  VkSurfaceCapabilitiesKHR capabilities;
  std::vector<VkSurfaceFormatKHR> formats;
  std::vector<VkPresentModeKHR> presentModes;
};

struct QueueFamilyIndices {
  uint32_t graphicsFamily;
  uint32_t presentFamily;
  bool graphicsFamilyHasValue = false;
  bool presentFamilyHasValue = false;
  bool isComplete() { return graphicsFamilyHasValue && presentFamilyHasValue; }
};

class DeviceImpl {
	public:
		static const bool enableValidationLayers = true;

		DeviceImpl(bebone::gfx::Window &window);
		~DeviceImpl();

		// Not copyable or movable
		DeviceImpl(const DeviceImpl &) = delete;
		void operator=(const DeviceImpl &) = delete;
		DeviceImpl(DeviceImpl &&) = delete;
		DeviceImpl &operator=(DeviceImpl &&) = delete;

		// VkCommandPool getCommandPool() const { return commandPool; }
		VkDevice device() const { return device_; }
		VkSurfaceKHR surface() { return surface_; }
		VkQueue graphicsQueue() { return graphicsQueue_; }
		VkQueue presentQueue() { return presentQueue_; }

		SwapChainSupportDetails getSwapChainSupport() { return querySwapChainSupport(physicalDevice); }
		uint32_t findMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties);
		QueueFamilyIndices findPhysicalQueueFamilies() { return findQueueFamilies(physicalDevice); }
		VkFormat findSupportedFormat(const std::vector<VkFormat> &candidates, VkImageTiling tiling, VkFormatFeatureFlags features);

		// Buffer Helper Functions
		// void createBuffer(VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, VkBuffer &buffer, VkDeviceMemory &bufferMemory);
		void createImageWithInfo(const VkImageCreateInfo &imageInfo, VkMemoryPropertyFlags properties, VkImage &image, VkDeviceMemory &imageMemory);

		VkPhysicalDeviceProperties properties;

	private:
		void createInstance();
		void setupDebugMessenger();
		void createSurface();
		void pickPhysicalDevice();
		void createLogicalDevice();
		// void createCommandPool();

		// helper functions
		bool isDeviceSuitable(VkPhysicalDevice device);
		static std::vector<const char *> getRequiredExtensions();
		bool checkValidationLayerSupport();
		QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device);
		void populateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT &createInfo);
		static void hasGflwRequiredInstanceExtensions();
		bool checkDeviceExtensionSupport(VkPhysicalDevice device);
		SwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice device);

		VkInstance instance;
		VkDebugUtilsMessengerEXT debugMessenger;

		
		VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
		bebone::gfx::Window &window;
		// VkCommandPool commandPool;

		VkDevice device_;
		VkSurfaceKHR surface_;
		VkQueue graphicsQueue_;
		VkQueue presentQueue_;

		const std::vector<const char *> validationLayers = { "VK_LAYER_KHRONOS_validation" };
		const std::vector<const char *> deviceExtensions = { VK_KHR_SWAPCHAIN_EXTENSION_NAME };
};

#endif