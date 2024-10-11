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
#include "vulkan_render_pass.h"
#include "vulkan_framebuffer.h"

namespace bebone::gfx {
    VulkanDevice::VulkanDevice(VulkanInstance& instance, std::unique_ptr<Window>& window) : instance_owner(instance) {
        auto& vulkan_window = *static_cast<VulkanWindow*>(window.get());
        vulkan_window.create_window_surface(instance.instance, &surface);

        pick_physical_device(instance);
        create_logical_device();

        command_buffer_pool = create_command_buffer_pool();

        LOG_TRACE("Created Vulkan device");
    }

    VulkanDevice::~VulkanDevice() {
        wait_idle();

        command_buffer_pool.reset();

        vkDestroyDevice(device, nullptr);

        LOG_DEBUG("TODO, destroy surface KHR");
        vkDestroySurfaceKHR(instance_owner.instance, surface, nullptr);

        LOG_TRACE("Destroyed Vulkan device");
    }

    void VulkanDevice::pick_physical_device(VulkanInstance& instance) {
        auto chooser = VulkanDeviceChooser();

        physical_device = chooser.get_physical_device(instance, surface);

        vkGetPhysicalDeviceProperties(physical_device, &properties);

        LOG_INFORMATION("Physical device: {}", properties.deviceName);
    }

    std::unique_ptr<VulkanDescriptorPool> VulkanDevice::create_descriptor_pool() {
        return std::make_unique<VulkanDescriptorPool>(*this);;
    }

    std::unique_ptr<VulkanDescriptorSetLayout> VulkanDevice::create_descriptor_set_layout(const std::vector<VulkanDescriptorSetLayoutBinding>& bindings) {
        return std::make_unique<VulkanDescriptorSetLayout>(*this, bindings);
    }

    std::unique_ptr<VulkanRenderTarget> VulkanDevice::create_render_target(std::unique_ptr<VulkanRenderPass>& render_pass) {
        return std::make_unique<VulkanRenderTarget>(*this, render_pass);
    }

    std::unique_ptr<VulkanRenderTarget>  VulkanDevice::create_render_target(
        std::unique_ptr<VulkanRenderPass>& render_pass,
        std::vector<std::unique_ptr<VulkanSwapChainImage>>& images
    ) {
        return std::make_unique<VulkanRenderTarget>(*this, render_pass, images);;
    }

    std::unique_ptr<VulkanSwapChain> VulkanDevice::create_swap_chain(std::unique_ptr<Window> &window) {
        return std::make_unique<VulkanSwapChain>(*this, VkExtent2D { static_cast<uint32_t>(window->get_width()), static_cast<uint32_t>(window->get_height()) });;
    }

    std::unique_ptr<VulkanPipelineLayout> VulkanDevice::create_pipeline_layout(const std::vector<std::unique_ptr<VulkanDescriptorSetLayout>>& layouts, const std::vector<VulkanConstRange>& constant_ranges) {
        return std::make_unique<VulkanPipelineLayout>(*this, layouts, constant_ranges);
    }

    std::unique_ptr<VulkanCommandBufferPool> VulkanDevice::create_command_buffer_pool() {
        return std::make_unique<VulkanCommandBufferPool>(*this);
    }

    std::unique_ptr<VulkanCommandBuffer> VulkanDevice::create_command_buffer() {
        return std::make_unique<VulkanCommandBuffer>(*this, *command_buffer_pool);
    }

    std::vector<std::unique_ptr<VulkanCommandBuffer>> VulkanDevice::create_command_buffers(const size_t& count) {
        auto command_buffers = std::vector<std::unique_ptr<VulkanCommandBuffer>> {};
        command_buffers.reserve(count);

        for(size_t i = 0; i < count; ++i)
            command_buffers.push_back(create_command_buffer());

        return command_buffers;
    }

    std::unique_ptr<VulkanCommandBuffer> VulkanDevice::begin_single_time_commands() {
        auto command_buffer = command_buffer_pool->create_command_buffer();

        command_buffer->begin_record();

        return command_buffer;
    }

    void VulkanDevice::end_single_time_commands(std::unique_ptr<VulkanCommandBuffer>& command_buffer) {
        command_buffer->end_record();

        VkSubmitInfo submit_info{};
        submit_info.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
        submit_info.commandBufferCount = 1;
        submit_info.pCommandBuffers = &command_buffer->backend;

        vkQueueSubmit(graphics_queue, 1, &submit_info, VK_NULL_HANDLE);
        vkQueueWaitIdle(graphics_queue);

        vkFreeCommandBuffers(device, command_buffer_pool->backend, 1, &command_buffer->backend);
    }

    std::unique_ptr<VulkanPipeline> VulkanDevice::create_pipeline(
        const std::unique_ptr<VulkanRenderPass>& render_pass,
        VulkanPipelineLayout& pipeline_layout,
        const std::vector<std::unique_ptr<VulkanShaderModule>>& shader_modules,
        VulkanPipelineConfig config_info
    ) {
        return std::make_unique<VulkanPipeline>(*this, render_pass, pipeline_layout, shader_modules, config_info);;
    }

    std::unique_ptr<VulkanPipeline> VulkanDevice::create_pipeline(
        const std::unique_ptr<VulkanRenderPass>& render_pass,
        VulkanPipelineLayout& pipeline_layout,
        const std::string& vertex_shader_path,
        const std::string& fragment_shader_path,
        VulkanPipelineConfig config_info
    ) {
        std::vector<std::unique_ptr<VulkanShaderModule>> shader_modules;
        shader_modules.push_back(create_shader_module(utils_read_file(vertex_shader_path), ShaderType::VertexShader));
        shader_modules.push_back(create_shader_module(utils_read_file(fragment_shader_path), ShaderType::FragmentShader));

        return std::make_unique<VulkanPipeline>(*this, render_pass, pipeline_layout, shader_modules, config_info);;
    }

    std::unique_ptr<VulkanRenderPass> VulkanDevice::create_render_pass(VkExtent2D extent, const std::vector<VulkanAttachmentDesc>& attachments) {
        return std::make_unique<VulkanRenderPass>(*this, extent, attachments);;
    }

    std::unique_ptr<VulkanFramebuffer> VulkanDevice::create_framebuffer(
        std::vector<std::unique_ptr<IVulkanImageView>>& attachments,
        std::unique_ptr<VulkanRenderPass>& render_pass,
        VkExtent2D extent
    ) {
        return std::make_unique<VulkanFramebuffer>(*this, attachments, render_pass, extent);
    }

    std::vector<std::unique_ptr<VulkanFramebuffer>> VulkanDevice::create_framebuffers(
        std::vector<std::unique_ptr<IVulkanImageView>>& attachments,
        std::unique_ptr<VulkanRenderPass>& render_pass,
        VkExtent2D extent,
        const size_t& count
    ) {
        auto framebuffers = std::vector<std::unique_ptr<VulkanFramebuffer>> {};
        framebuffers.reserve(count);

        for(size_t i = 0; i < count; ++i)
            framebuffers.push_back(create_framebuffer(attachments, render_pass, extent));

        return framebuffers;
    }

    std::unique_ptr<VulkanShaderModule> VulkanDevice::create_shader_module(const std::string& source_code, const ShaderType& type) {
        auto shader_compiler = SpirVShaderCompiler();

        shader_compiler.add_shader_source(ShaderSource(
            source_code,
            type
        ));

        auto shader_code = shader_compiler.compile(type);

        return std::make_unique<VulkanShaderModule>(*this, shader_code);;
    }

    std::unique_ptr<VulkanPipelineManager> VulkanDevice::create_pipeline_manager() {
        return std::make_unique<VulkanPipelineManager>(*this);;
    }

    void VulkanDevice::create_logical_device() {
        auto indices = VulkanDeviceChooser::find_queue_families(physical_device, surface);

        auto unique_queue_families = std::set<uint32_t> { indices.graphics_family, indices.present_family };

        auto queue_create_infos = std::vector<VkDeviceQueueCreateInfo> {};
        queue_create_infos.reserve(unique_queue_families.size());

        float queue_priority = 1.0f;

        for(const auto& queue_family : unique_queue_families) {
            VkDeviceQueueCreateInfo queue_create_info = {};

            queue_create_info.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
            queue_create_info.queueFamilyIndex = queue_family;
            queue_create_info.queueCount = 1;
            queue_create_info.pQueuePriorities = &queue_priority;

            queue_create_infos.push_back(queue_create_info);
        }

        VkDeviceCreateInfo create_info = {};
        create_info.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;

        create_info.queueCreateInfoCount = static_cast<uint32_t>(queue_create_infos.size());
        create_info.pQueueCreateInfos = queue_create_infos.data();
        create_info.pEnabledFeatures = nullptr;
        create_info.enabledExtensionCount = static_cast<uint32_t>(VulkanDeviceChooser::device_extensions.size());
        create_info.ppEnabledExtensionNames = VulkanDeviceChooser::device_extensions.data();

        VkPhysicalDeviceDescriptorIndexingFeatures descriptor_indexing_features{};
        descriptor_indexing_features.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_DESCRIPTOR_INDEXING_FEATURES_EXT;
        descriptor_indexing_features.pNext = nullptr;
        descriptor_indexing_features.descriptorBindingSampledImageUpdateAfterBind = VK_TRUE;
        descriptor_indexing_features.descriptorBindingPartiallyBound = VK_TRUE;
        descriptor_indexing_features.descriptorBindingVariableDescriptorCount = VK_TRUE;
        descriptor_indexing_features.descriptorBindingUniformBufferUpdateAfterBind = VK_TRUE;
        descriptor_indexing_features.shaderUniformBufferArrayNonUniformIndexing = VK_TRUE;
        descriptor_indexing_features.runtimeDescriptorArray  = VK_TRUE;

        VkPhysicalDeviceFeatures2 device_features_2{};
        device_features_2.features.samplerAnisotropy = VK_TRUE;
        device_features_2.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_FEATURES_2;
        device_features_2.pNext = &descriptor_indexing_features;

        create_info.pNext = &device_features_2;
        create_info.enabledLayerCount = 0;

        if(vkCreateDevice(physical_device, &create_info, nullptr, &device) != VK_SUCCESS) {
            LOG_ERROR("Failed to create logical device");
            throw std::runtime_error("failed to create logical device!");
        }

        vkGetDeviceQueue(device, indices.graphics_family, 0, &graphics_queue);
        vkGetDeviceQueue(device, indices.present_family, 0, &present_queue);
    }

    VkFormat VulkanDevice::find_supported_format(
        const std::vector<VkFormat> &candidates,
        VkImageTiling tiling,
        VkFormatFeatureFlags features
    ) {
        for(const auto& format : candidates) {
            VkFormatProperties props;

            vkGetPhysicalDeviceFormatProperties(physical_device, format, &props);

            if(tiling == VK_IMAGE_TILING_LINEAR && (props.linearTilingFeatures & features) == features)
                return format;
            else if(tiling == VK_IMAGE_TILING_OPTIMAL && (props.optimalTilingFeatures & features) == features)
                return format;
        }

        LOG_ERROR("Failed to find supported format");
        throw std::runtime_error("failed to find supported format!");
    }

    uint32_t VulkanDevice::find_memory_type(uint32_t type_filter, VkMemoryPropertyFlags mem_properties) {
        VkPhysicalDeviceMemoryProperties physical_properties;
        vkGetPhysicalDeviceMemoryProperties(physical_device, &physical_properties);

        for(uint32_t i = 0; i < physical_properties.memoryTypeCount; i++) {
            if((type_filter & (1 << i)) && (physical_properties.memoryTypes[i].propertyFlags & mem_properties) == mem_properties)
                return i;
        }

        LOG_ERROR("Failed to find suitable memory type");
        throw std::runtime_error("failed to find suitable memory type!");
    }

    void VulkanDevice::wait_idle() {
        vkDeviceWaitIdle(device);
    }

    VkFormat VulkanDevice::find_depth_format() {
        return find_supported_format(
            {VK_FORMAT_D32_SFLOAT, VK_FORMAT_D32_SFLOAT_S8_UINT, VK_FORMAT_D24_UNORM_S8_UINT},
            VK_IMAGE_TILING_OPTIMAL,
            VK_FORMAT_FEATURE_DEPTH_STENCIL_ATTACHMENT_BIT);
    }
}
