#include "vulkan_device.h"

bebone::gfx::VulkanDevice::VulkanDevice(bebone::gfx::Window &window, bebone::gfx::VulkanInstance& _vulkanInstance) : window{window}, vulkanInstance(_vulkanInstance) {
	createSurface(_vulkanInstance);

	pickPhysicalDevice(_vulkanInstance);
	createLogicalDevice();
}

bebone::gfx::VulkanDevice::~VulkanDevice() {
	vkDestroyDevice(device_, nullptr);
	vkDestroySurfaceKHR(vulkanInstance.get_instance(), surface_, nullptr);
}

void bebone::gfx::VulkanDevice::pickPhysicalDevice(bebone::gfx::VulkanInstance& vulkanInstance) {
    VulkanDeviceChooser chooser;

    physicalDevice = chooser.get_physical_device(vulkanInstance, surface_);

    vkGetPhysicalDeviceProperties(physicalDevice, &properties);
    std::cout << "physical device: " << properties.deviceName << std::endl;
}

void bebone::gfx::VulkanDevice::createLogicalDevice() {
	QueueFamilyIndices indices = VulkanDeviceChooser::findQueueFamilies(physicalDevice, surface_);

	std::vector<VkDeviceQueueCreateInfo> queueCreateInfos;
	std::set<uint32_t> uniqueQueueFamilies = {indices.graphicsFamily, indices.presentFamily};

	float queuePriority = 1.0f;
	for (uint32_t queueFamily : uniqueQueueFamilies) {
		VkDeviceQueueCreateInfo queueCreateInfo = {};
		queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
		queueCreateInfo.queueFamilyIndex = queueFamily;
		queueCreateInfo.queueCount = 1;
		queueCreateInfo.pQueuePriorities = &queuePriority;
		queueCreateInfos.push_back(queueCreateInfo);
	}

	// VkPhysicalDeviceFeatures deviceFeatures = {};
	// deviceFeatures.samplerAnisotropy = VK_TRUE;

	VkDeviceCreateInfo createInfo = {};
	createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;

	createInfo.queueCreateInfoCount = static_cast<uint32_t>(queueCreateInfos.size());
	createInfo.pQueueCreateInfos = queueCreateInfos.data();

	// createInfo.pEnabledFeatures = &deviceFeatures;
	createInfo.pEnabledFeatures = nullptr;
	createInfo.enabledExtensionCount = static_cast<uint32_t>(VulkanDeviceChooser::deviceExtensions.size());
	createInfo.ppEnabledExtensionNames = VulkanDeviceChooser::deviceExtensions.data();

	VkPhysicalDeviceDescriptorIndexingFeatures descriptorIndexingFeatures{};
	descriptorIndexingFeatures.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_DESCRIPTOR_INDEXING_FEATURES_EXT;
	descriptorIndexingFeatures.pNext = nullptr;
	descriptorIndexingFeatures.descriptorBindingSampledImageUpdateAfterBind = VK_TRUE;
	descriptorIndexingFeatures.descriptorBindingPartiallyBound = VK_TRUE;
	descriptorIndexingFeatures.descriptorBindingVariableDescriptorCount = VK_TRUE;
	descriptorIndexingFeatures.descriptorBindingUniformBufferUpdateAfterBind = VK_TRUE;
	descriptorIndexingFeatures.shaderUniformBufferArrayNonUniformIndexing = VK_TRUE;
	descriptorIndexingFeatures.runtimeDescriptorArray  = VK_TRUE;

	VkPhysicalDeviceFeatures2 deviceFeatures2{};
	deviceFeatures2.features.samplerAnisotropy = VK_TRUE;

	deviceFeatures2.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_FEATURES_2;
	deviceFeatures2.pNext = &descriptorIndexingFeatures;
	
	createInfo.pNext = &deviceFeatures2;

	// might not really be necessary anymore because device specific validation layers
	// have been deprecated
	// if (enableValidationLayers) {
	// 	createInfo.enabledLayerCount = static_cast<uint32_t>(validationLayers.size());
	// 	createInfo.ppEnabledLayerNames = validationLayers.data();
	// } else {
		createInfo.enabledLayerCount = 0;
	// }

	if (vkCreateDevice(physicalDevice, &createInfo, nullptr, &device_) != VK_SUCCESS) {
		throw std::runtime_error("failed to create logical device!");
	}

	vkGetDeviceQueue(device_, indices.graphicsFamily, 0, &graphicsQueue_);
	vkGetDeviceQueue(device_, indices.presentFamily, 0, &presentQueue_);
}

void bebone::gfx::VulkanDevice::createSurface(bebone::gfx::VulkanInstance& vulkanInstance) {
    window.createWindowSurface(vulkanInstance.get_instance(), &surface_);
}

VkFormat bebone::gfx::VulkanDevice::findSupportedFormat(const std::vector<VkFormat> &candidates, VkImageTiling tiling, VkFormatFeatureFlags features) {
	for (VkFormat format : candidates) {
		VkFormatProperties props;
		vkGetPhysicalDeviceFormatProperties(physicalDevice, format, &props);

		if (tiling == VK_IMAGE_TILING_LINEAR && (props.linearTilingFeatures & features) == features) {
			return format;
		} else if (
			tiling == VK_IMAGE_TILING_OPTIMAL && (props.optimalTilingFeatures & features) == features) {
			return format;
		}
	}

	throw std::runtime_error("failed to find supported format!");
}

uint32_t bebone::gfx::VulkanDevice::findMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties) {
	VkPhysicalDeviceMemoryProperties memProperties;
	vkGetPhysicalDeviceMemoryProperties(physicalDevice, &memProperties);

	for (uint32_t i = 0; i < memProperties.memoryTypeCount; i++) {
		if ((typeFilter & (1 << i)) && (memProperties.memoryTypes[i].propertyFlags & properties) == properties) {
			return i;
		}
	}

	throw std::runtime_error("failed to find suitable memory type!");
}

void bebone::gfx::VulkanDevice::createImageWithInfo(const VkImageCreateInfo &imageInfo, VkMemoryPropertyFlags properties, VkImage &image, VkDeviceMemory &imageMemory) {
	if (vkCreateImage(device_, &imageInfo, nullptr, &image) != VK_SUCCESS) {
		throw std::runtime_error("failed to create image!");
	}

	VkMemoryRequirements memRequirements;
	vkGetImageMemoryRequirements(device_, image, &memRequirements);

	VkMemoryAllocateInfo allocInfo{};
	allocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
	allocInfo.allocationSize = memRequirements.size;
	allocInfo.memoryTypeIndex = findMemoryType(memRequirements.memoryTypeBits, properties);

	if (vkAllocateMemory(device_, &allocInfo, nullptr, &imageMemory) != VK_SUCCESS) {
		throw std::runtime_error("failed to allocate image memory!");
	}

	if (vkBindImageMemory(device_, image, imageMemory, 0) != VK_SUCCESS) {
		throw std::runtime_error("failed to bind image memory!");
	}
}
