#include "vulkan_device.h"

#include "vulkan_sampler.h"

#include "vulkan_swap_chain.h"

#include "vulkan_descriptor_pool.h"
#include "vulkan_descriptor_set.h"
#include "vulkan_descriptor_set_layout.h"

#include "vulkan_command_buffer_pool.h"
#include "vulkan_pipeline_layout.h"
#include "vulkan_pipeline.h"
#include "vulkan_shader_module.h"
#include "vulkan_descriptor_set_layout_binding.h"
#include "vulkan_const_range.h"
#include "vulkan_pipeline_manager.h"

#include "../shaders/spirv_shader_compiler.h"

namespace bebone::gfx::vulkan {
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
        return std::make_shared<VulkanDescriptorPool>(*this);
    }

    // Todo add bufferInfo offset there
    void VulkanDevice::update_descriptor_set(
        const std::shared_ptr<VulkanBuffer>& buffer,
        std::shared_ptr<VulkanDescriptorSet>& descriptorSet,
        const size_t& binding,
        const size_t& dstArrayElement
    ) {
        VkDescriptorBufferInfo bufferInfo{};
        bufferInfo.buffer = buffer->backend;
        bufferInfo.offset = 0;
        bufferInfo.range = buffer->get_size();

        VkWriteDescriptorSet descriptorWrite{};
        descriptorWrite.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;

        descriptorWrite.dstSet = descriptorSet->backend;
        descriptorWrite.dstBinding = binding;
        descriptorWrite.dstArrayElement = dstArrayElement;
        // Todo, remember that this mean \/
        // Todo THIS IS A HANDLE, and handle counter should work per shader binding, not a cpu binding thing

        descriptorWrite.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
        descriptorWrite.descriptorCount = 1;
        descriptorWrite.pBufferInfo = &bufferInfo;

        descriptorWrite.pImageInfo = nullptr; // Optional
        descriptorWrite.pTexelBufferView = nullptr; // Optional

        vkUpdateDescriptorSets(device_, 1, &descriptorWrite, 0, nullptr);
    }

    void VulkanDevice::update_descriptor_set(
        const std::shared_ptr<VulkanTexture>& texture,
        std::shared_ptr<VulkanDescriptorSet>& descriptorSet,
        const size_t& binding,
        const size_t& dstArrayElement
    ) {
        const auto& [image, memory, view, sampler] = *texture;
        update_descriptor_set(sampler, view, descriptorSet, binding, dstArrayElement);
    }

    void VulkanDevice::update_descriptor_set(
        const std::shared_ptr<VulkanSampler>& sampler,
        const std::shared_ptr<VulkanImageView>& view,
        const std::shared_ptr<VulkanDescriptorSet>& descriptorSet,
        const size_t& binding,
        const size_t& dstArrayElement
    ) {
        VkDescriptorImageInfo imageInfo{};
        imageInfo.sampler = sampler->backend;
        imageInfo.imageView = view->backend;
        imageInfo.imageLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL; // Todo, remove this hard coded cringe

        VkWriteDescriptorSet descriptorWrite{};
        descriptorWrite.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;

        descriptorWrite.dstSet = descriptorSet->backend;
        descriptorWrite.dstBinding = binding;
        descriptorWrite.dstArrayElement = dstArrayElement; // Todo THIS IS A HANDLE, and handle counter should work per shader binding, not a cpu binding thing

        descriptorWrite.descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
        descriptorWrite.descriptorCount = 1;
        // descriptorWrite.pBufferInfo = &bufferInfo;
        descriptorWrite.pImageInfo = &imageInfo;

        // descriptorWrite.pImageInfo = nullptr; // Optional
        descriptorWrite.pTexelBufferView = nullptr; // Optional

        vkUpdateDescriptorSets(device_, 1, &descriptorWrite, 0, nullptr);
    }

    void VulkanDevice::update_descriptor_set(
            VulkanBufferMemoryTuple& tuple,
            std::shared_ptr<VulkanDescriptorSet>& descriptorSet,
            const size_t& binding,
            const size_t& dstArrayElement
    ) {
        update_descriptor_set(
            tuple.buffer,
            descriptorSet,
            binding,
            dstArrayElement
        );
    }

    void VulkanDevice::update_descriptor_sets(
            std::vector<std::shared_ptr<VulkanBuffer>>& buffers,
            std::vector<std::shared_ptr<VulkanDescriptorSet>>& descriptorSets,
            const size_t& binding,
            const std::vector<size_t>& dstArrayElements
    ) {
        if(buffers.size() != dstArrayElements.size())
            throw std::runtime_error("buffer an dstArrayElements count is not matching");

        for(size_t i = 0; i < dstArrayElements.size(); ++i) {
            auto& buffer = buffers[i];
            auto& dstArrayElement = dstArrayElements[i];
            auto& descriptorSet = descriptorSets[i];

            update_descriptor_set(buffer, descriptorSet, binding, dstArrayElement);
        }
    }

    void VulkanDevice::update_descriptor_sets(
            const std::vector<VulkanBufferMemoryTuple>& tuples,
            std::vector<std::shared_ptr<VulkanDescriptorSet>>& descriptorSets,
            const size_t& binding,
            const std::vector<size_t>& dstArrayElements
    ) {
        if(tuples.size() != dstArrayElements.size())
            throw std::runtime_error("buffer an dstArrayElements count is not matching");

        for(size_t i = 0; i < dstArrayElements.size(); ++i) {
            const auto& buffer = tuples[i].buffer;
            const auto& dstArrayElement = dstArrayElements[i];
            auto& descriptorSet = descriptorSets[i];

            update_descriptor_set(buffer, descriptorSet, binding, dstArrayElement);
        }
    }

    void VulkanDevice::update_descriptor_sets(
            std::shared_ptr<VulkanTexture>& texture,
            std::vector<std::shared_ptr<VulkanDescriptorSet>>& descriptorSets,
            const size_t& binding,
            const std::vector<size_t>& dstArrayElements
    ) {
        for(size_t i = 0; i < dstArrayElements.size(); ++i) {
            auto& dstArrayElement = dstArrayElements[i];
            auto& descriptorSet = descriptorSets[i];

            update_descriptor_set(texture, descriptorSet, binding, dstArrayElement);
        }
    }

    std::shared_ptr<VulkanDescriptorSetLayout> VulkanDevice::create_descriptor_set_layout(const std::vector<VulkanDescriptorSetLayoutBinding>& bindings) {
        return std::make_shared<VulkanDescriptorSetLayout>(*this, bindings);
    }

    // Todo why there is a vector ?
    std::vector<std::shared_ptr<VulkanDescriptorSetLayout>> VulkanDevice::create_descriptor_set_layouts(const std::vector<VulkanDescriptorSetLayoutBinding>& bindings) {
        return { create_descriptor_set_layout(bindings) };
    }

    std::shared_ptr<VulkanSwapChain> VulkanDevice::create_swap_chain(std::shared_ptr<Window> &window) {
        return std::make_shared<VulkanSwapChain>(*this, VkExtent2D { static_cast<uint32_t>(window->get_width()), static_cast<uint32_t>(window->get_height()) });
    }

    std::shared_ptr<VulkanPipelineLayout> VulkanDevice::create_pipeline_layout(const std::vector<std::shared_ptr<VulkanDescriptorSetLayout>>& layouts, const std::vector<VulkanConstRange>& constantRanges) {
        return std::make_shared<VulkanPipelineLayout>(*this, layouts, constantRanges);
    }

    std::shared_ptr<VulkanCommandBufferPool> VulkanDevice::create_command_buffer_pool() {
        return std::make_shared<VulkanCommandBufferPool>(*this);
    }

    std::shared_ptr<VulkanDeviceMemory> VulkanDevice::create_device_memory(VkMemoryRequirements memRequirements, VkMemoryPropertyFlags properties) {
        return std::make_shared<VulkanDeviceMemory>(*this, memRequirements, properties);
    }

    std::shared_ptr<VulkanBuffer> VulkanDevice::create_buffer(const size_t& size, VulkanBufferInfo bufferInfo) {
        return std::make_shared<VulkanBuffer>(*this, size, bufferInfo);
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
            buffers.push_back(std::make_shared<VulkanBuffer>(*this, size, bufferInfo));

        return buffers;
    }

    std::vector<VulkanBufferMemoryTuple> VulkanDevice::create_buffer_memorys(const size_t& size, const size_t& bufferCount, VulkanBufferInfo bufferInfo) {
        std::vector<VulkanBufferMemoryTuple> tuples;

        for(size_t i = 0; i < bufferCount; ++i)
            tuples.emplace_back(create_buffer_memory(size, bufferInfo));

        return tuples;
    }

    std::shared_ptr<VulkanImage> VulkanDevice::create_image(VkFormat format, VkExtent3D extent, VulkanImageInfo imageInfo) {
        return std::make_shared<VulkanImage>(*this, format, extent, imageInfo);
    }

    VulkanImageMemoryTuple VulkanDevice::create_image_memory(VkFormat format, VkExtent3D extent, VulkanImageInfo imageInfo) {
        auto image = std::make_shared<VulkanImage>(*this, format, extent, imageInfo);

        auto req = image->get_memory_requirements(*this);

        auto memory = create_device_memory(req, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);
        memory->bind_image_memory(*this, image);

        return { image, memory };
    }

    // Todo Why this function is public ?, and probably could be static
    std::shared_ptr<VulkanImage> VulkanDevice::create_image(VkImage& image) {
        return std::make_shared<VulkanImage>(image);
    }

    std::shared_ptr<VulkanSampler> VulkanDevice::create_sampler() {
        return std::make_shared<VulkanSampler>(*this);
    }

    std::shared_ptr<VulkanImageView> VulkanDevice::create_image_view(VulkanImage& image, const VkFormat& imageFormat, VulkanImageViewInfo imageViewInfo) {
        return std::make_shared<VulkanImageView>(*this, image, imageFormat, imageViewInfo);
    }

    std::shared_ptr<VulkanPipeline> VulkanDevice::create_pipeline(
        std::shared_ptr<VulkanSwapChain>& swapChain,
        std::shared_ptr<VulkanPipelineLayout>& pipelineLayout,
        std::vector<std::shared_ptr<VulkanShaderModule>> shaderModules,
        VulkanPipelineConfig configInfo
    ) {

        return std::make_shared<VulkanPipeline>(*this, swapChain, pipelineLayout, shaderModules, configInfo);
    }

    std::shared_ptr<VulkanShaderModule> VulkanDevice::create_shader_module(const std::string& shaderCodePath, const ShaderType& type) {
        SpirVShaderCompiler shaderCompiler;

        shaderCompiler.add_shader_source(ShaderSource(
            vulkan_device_read_file(shaderCodePath),
            type
        ));

        gfx::ShaderCode shadeCode = shaderCompiler.compile(type);

        return std::make_shared<VulkanShaderModule>(*this, shadeCode);
    }

    std::shared_ptr<VulkanTexture> VulkanDevice::create_texture(
            std::shared_ptr<VulkanCommandBufferPool>& commandBufferPool,
            const std::string& filePath
    ) {
        auto raw = assets::Image<ColorRGBA>::load_from_file(filePath);
        return std::make_shared<VulkanTexture>(*this, commandBufferPool, raw);
    }

    std::shared_ptr<VulkanPipelineManager> VulkanDevice::create_pipeline_manager() {
        return std::make_shared<VulkanPipelineManager>(*this);
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
