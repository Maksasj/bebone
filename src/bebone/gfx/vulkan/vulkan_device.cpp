#include "vulkan_device.h"

#include "vulkan_sampler.h"
#include "vulkan_swap_chain.h"
#include "vulkan_descriptor_pool.h"
#include "vulkan_descriptor_set_layout.h"
#include "vulkan_command_buffer_pool.h"
#include "vulkan_pipeline_layout.h"
#include "vulkan_pipeline.h"
#include "vulkan_shader_module.h"
#include "vulkan_descriptor_set_layout_binding.h"
#include "vulkan_const_range.h"
#include "vulkan_pipeline_manager.h"

namespace bebone::gfx::vulkan {
    // Todo, move this
    std::string vulkan_device_read_file(const std::string& path) {
        std::ifstream file(path);
        std::stringstream ss;
        ss << file.rdbuf();
        return ss.str();
    }

    VulkanDevice::VulkanDevice(VulkanInstance& _vulkanInstance, VulkanWindow &window) : vulkanInstance(_vulkanInstance) {
        window.create_window_surface(vulkanInstance.get_instance(), &surface_);

        pick_physical_device(_vulkanInstance);
        create_logical_device();
    }

    void VulkanDevice::pick_physical_device(VulkanInstance& vulkanInstance) {
        VulkanDeviceChooser chooser;

        physicalDevice = chooser.get_physical_device(vulkanInstance, surface_);

        vkGetPhysicalDeviceProperties(physicalDevice, &properties);
        std::cout << "physical device: " << properties.deviceName << std::endl;
    }

    std::shared_ptr<VulkanDescriptorPool> VulkanDevice::create_descriptor_pool() {
        auto descriptor_pool = std::make_shared<VulkanDescriptorPool>(*this);

        child_objects.push_back(descriptor_pool);

        return descriptor_pool;
    }

    // Todo why there is a vector ?
    std::vector<std::shared_ptr<VulkanDescriptorSetLayout>> VulkanDevice::create_descriptor_set_layouts(const std::vector<VulkanDescriptorSetLayoutBinding>& bindings) {
        auto descriptor_set_layout = std::make_shared<VulkanDescriptorSetLayout>(*this, bindings);

        child_objects.push_back(descriptor_set_layout);

        return { descriptor_set_layout };
    }

    std::shared_ptr<VulkanSwapChain> VulkanDevice::create_swap_chain(std::shared_ptr<Window> &window) {
        auto swap_chain = std::make_shared<VulkanSwapChain>(*this, VkExtent2D { static_cast<uint32_t>(window->get_width()), static_cast<uint32_t>(window->get_height()) });

        child_objects.push_back(swap_chain);

        return swap_chain;
    }

    std::shared_ptr<VulkanPipelineLayout> VulkanDevice::create_pipeline_layout(const std::vector<std::shared_ptr<VulkanDescriptorSetLayout>>& layouts, const std::vector<VulkanConstRange>& constantRanges) {
        auto pipeline_layout = std::make_shared<VulkanPipelineLayout>(*this, layouts, constantRanges);

        child_objects.push_back(pipeline_layout);

        return pipeline_layout;
    }

    std::shared_ptr<VulkanCommandBufferPool> VulkanDevice::create_command_buffer_pool() {
        auto command_buffer_pool = std::make_shared<VulkanCommandBufferPool>(*this);

        child_objects.push_back(command_buffer_pool);

        return command_buffer_pool;
    }

    std::shared_ptr<VulkanDeviceMemory> VulkanDevice::create_device_memory(VkMemoryRequirements memRequirements, VkMemoryPropertyFlags properties) {
        auto device_memory = std::make_shared<VulkanDeviceMemory>(*this, memRequirements, properties);

        child_objects.push_back(device_memory);

        return device_memory;
    }

    std::shared_ptr<VulkanBuffer> VulkanDevice::create_buffer(const size_t& size, VulkanBufferInfo bufferInfo) {
        auto buffer = std::make_shared<VulkanBuffer>(*this, size, bufferInfo);

        child_objects.push_back(buffer);

        return buffer;
    }

    VulkanBufferMemoryTuple VulkanDevice::create_buffer_memory(const size_t& size, VulkanBufferInfo bufferInfo) {
        auto buffer = create_buffer(size, bufferInfo);

        auto memRequirements = buffer->get_memory_requirements(*this);

        auto memory = create_device_memory(memRequirements, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT); // Todo this should be configurable
        memory->bind_buffer_memory(*this, buffer);

        return { buffer, memory };
    }

    std::vector<std::shared_ptr<VulkanBuffer>> VulkanDevice::create_buffers(const size_t& size, const size_t& bufferCount, VulkanBufferInfo bufferInfo) {
        std::vector<std::shared_ptr<VulkanBuffer>> buffers;

        for(size_t i = 0; i < bufferCount; ++i)
            buffers.push_back(create_buffer(size, bufferInfo));

        return buffers;
    }

    std::vector<VulkanBufferMemoryTuple> VulkanDevice::create_buffer_memorys(const size_t& size, const size_t& bufferCount, VulkanBufferInfo bufferInfo) {
        std::vector<VulkanBufferMemoryTuple> tuples;

        for(size_t i = 0; i < bufferCount; ++i)
            tuples.emplace_back(create_buffer_memory(size, bufferInfo));

        return tuples;
    }

    std::shared_ptr<VulkanImage> VulkanDevice::create_image(VkFormat format, VkExtent3D extent, VulkanImageInfo imageInfo) {
        auto image = std::make_shared<VulkanImage>(*this, format, extent, imageInfo);

        child_objects.push_back(image);

        return image;
    }

    VulkanImageMemoryTuple VulkanDevice::create_image_memory(VkFormat format, VkExtent3D extent, VulkanImageInfo imageInfo) {
        auto image = std::make_shared<VulkanImage>(*this, format, extent, imageInfo);

        auto req = image->get_memory_requirements(*this);

        auto memory = create_device_memory(req, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);
        memory->bind_image_memory(*this, image);

        return make_tuple(image, memory);
    }

    // Todo Why this function is public ?, and probably could be static
    std::shared_ptr<VulkanImage> VulkanDevice::create_image(VkImage& image) {
        auto im = std::make_shared<VulkanImage>(image);

        child_objects.push_back(im);

        return im;
    }

    std::shared_ptr<VulkanSampler> VulkanDevice::create_sampler() {
        auto sampler = std::make_shared<VulkanSampler>(*this);

        child_objects.push_back(sampler);

        return sampler;
    }

    std::shared_ptr<VulkanImageView> VulkanDevice::create_image_view(VulkanImage& image, const VkFormat& imageFormat, VulkanImageViewInfo imageViewInfo) {
        auto view = std::make_shared<VulkanImageView>(*this, image, imageFormat, imageViewInfo);

        child_objects.push_back(view);

        return view;
    }

    std::shared_ptr<VulkanPipeline> VulkanDevice::create_pipeline(
        std::shared_ptr<VulkanSwapChain>& swapChain,
        std::shared_ptr<VulkanPipelineLayout>& pipelineLayout,
        std::vector<std::shared_ptr<VulkanShaderModule>> shaderModules,
        VulkanPipelineConfig configInfo
    ) {
        auto pipeline = std::make_shared<VulkanPipeline>(*this, swapChain, pipelineLayout, shaderModules, configInfo);

        child_objects.push_back(pipeline);

        return pipeline;
    }

    std::shared_ptr<VulkanShaderModule> VulkanDevice::create_shader_module(const std::string& shaderCodePath, const ShaderType& type) {
        SpirVShaderCompiler shaderCompiler;

        shaderCompiler.add_shader_source(ShaderSource(
            vulkan_device_read_file(shaderCodePath),
            type
        ));

        gfx::ShaderCode shadeCode = shaderCompiler.compile(type);

        auto shader = std::make_shared<VulkanShaderModule>(*this, shadeCode);

        child_objects.push_back(shader);

        return shader;
    }

    std::shared_ptr<VulkanTexture> VulkanDevice::create_texture(
            std::shared_ptr<VulkanCommandBufferPool>& commandBufferPool,
            const std::string& filePath
    ) {
        auto raw = assets::Image<ColorRGBA>::load_from_file(filePath);
        auto texture = std::make_shared<VulkanTexture>(*this, commandBufferPool, raw);

        child_objects.push_back(texture);

        return texture;
    }

    std::shared_ptr<VulkanPipelineManager> VulkanDevice::create_pipeline_manager() {
        auto pipeline_manager = std::make_shared<VulkanPipelineManager>(*this);

        child_objects.push_back(pipeline_manager);

        return pipeline_manager;
    }

    void VulkanDevice::create_logical_device() {
        QueueFamilyIndices indices = VulkanDeviceChooser::find_queue_families(physicalDevice, surface_);

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

    VkFormat VulkanDevice::find_supported_format(const std::vector<VkFormat> &candidates, VkImageTiling tiling, VkFormatFeatureFlags features) {
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

    uint32_t VulkanDevice::find_memory_type(uint32_t typeFilter, VkMemoryPropertyFlags properties) {
        VkPhysicalDeviceMemoryProperties memProperties;
        vkGetPhysicalDeviceMemoryProperties(physicalDevice, &memProperties);

        for (uint32_t i = 0; i < memProperties.memoryTypeCount; i++) {
            if ((typeFilter & (1 << i)) && (memProperties.memoryTypes[i].propertyFlags & properties) == properties) {
                return i;
            }
        }

        throw std::runtime_error("failed to find suitable memory type!");
    }

    void VulkanDevice::wait_idle() {
        vkDeviceWaitIdle(device_);
    }

    void VulkanDevice::destroy() {
        wait_idle();

        for(auto& child : child_objects) {
            if(!child->is_destroyed())
                destroy_all(child);
        }

        vkDestroyDevice(device_, nullptr);
        vkDestroySurfaceKHR(vulkanInstance.get_instance(), surface_, nullptr);
    }

    VkFormat VulkanDevice::find_depth_format() {
        return find_supported_format(
            {VK_FORMAT_D32_SFLOAT, VK_FORMAT_D32_SFLOAT_S8_UINT, VK_FORMAT_D24_UNORM_S8_UINT},
            VK_IMAGE_TILING_OPTIMAL,
            VK_FORMAT_FEATURE_DEPTH_STENCIL_ATTACHMENT_BIT);
    }
}
