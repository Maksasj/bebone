#include "vulkan_device.h"

#include "vulkan_swap_chain.h"
#include "vulkan_descriptor_pool.h"
#include "vulkan_command_buffer_pool.h"
#include "vulkan_pipeline_layout_impl.h"
#include "vulkan_pipeline_impl.h"

namespace bebone::gfx {
    VulkanDevice::VulkanDevice(VulkanWindow &window, VulkanInstance& _vulkanInstance) : window{window}, vulkanInstance(_vulkanInstance) {
        createSurface(_vulkanInstance);

        pickPhysicalDevice(_vulkanInstance);
        createLogicalDevice();
    }

    VulkanDevice::~VulkanDevice() {
        vkDestroyDevice(device_, nullptr);
        vkDestroySurfaceKHR(vulkanInstance.get_instance(), surface_, nullptr);
    }

    void VulkanDevice::pickPhysicalDevice(VulkanInstance& vulkanInstance) {
        VulkanDeviceChooser chooser;

        physicalDevice = chooser.get_physical_device(vulkanInstance, surface_);

        vkGetPhysicalDeviceProperties(physicalDevice, &properties);
        std::cout << "physical device: " << properties.deviceName << std::endl;
    }

    std::shared_ptr<VulkanDescriptorPool> VulkanDevice::create_descriptor_pool() {
        return std::make_shared<VulkanDescriptorPool>(*this);
    }

    std::shared_ptr<VulkanSwapChain> VulkanDevice::create_swap_chain(std::shared_ptr<Window> &window) {
        return std::make_shared<VulkanSwapChain>(*this, VkExtent2D { static_cast<uint32_t>(window->get_width()), static_cast<uint32_t>(window->get_height()) });
    }

    std::shared_ptr<VulkanPipelineLayoutImpl> VulkanDevice::create_pipeline_layout(std::shared_ptr<VulkanDescriptorPool>& pool, const std::vector<VkPushConstantRange>& constantRanges) {
        return std::make_shared<VulkanPipelineLayoutImpl>(*this, *pool, constantRanges);
    }

    std::shared_ptr<VulkanCommandBufferPool> VulkanDevice::create_command_buffer_pool() {
        return std::make_shared<VulkanCommandBufferPool>(*this);
    }

    std::shared_ptr<VulkanBufferImpl> VulkanDevice::create_buffer(const size_t& size) {
        return std::make_shared<VulkanBufferImpl>(size, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, *this);
    }

    void VulkanDevice::createLogicalDevice() {
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

    void VulkanDevice::createSurface(VulkanInstance& vulkanInstance) {
        window.create_window_surface(vulkanInstance.get_instance(), &surface_);
    }

    VkFormat VulkanDevice::findSupportedFormat(const std::vector<VkFormat> &candidates, VkImageTiling tiling, VkFormatFeatureFlags features) {
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

    uint32_t VulkanDevice::findMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties) {
        VkPhysicalDeviceMemoryProperties memProperties;
        vkGetPhysicalDeviceMemoryProperties(physicalDevice, &memProperties);

        for (uint32_t i = 0; i < memProperties.memoryTypeCount; i++) {
            if ((typeFilter & (1 << i)) && (memProperties.memoryTypes[i].propertyFlags & properties) == properties) {
                return i;
            }
        }

        throw std::runtime_error("failed to find suitable memory type!");
    }

    void VulkanDevice::createImageWithInfo(const VkImageCreateInfo &imageInfo, VkMemoryPropertyFlags properties, VkImage &image, VkDeviceMemory &imageMemory) {
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
}
