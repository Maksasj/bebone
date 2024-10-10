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
        vulkan_window.create_window_surface(instance.backend, &surface);

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
        vkDestroySurfaceKHR(instance_owner.backend, surface, nullptr);

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

    // Todo add buffer_info offset there
    void VulkanDevice::update_descriptor_set(
        IVulkanBuffer& buffer,
        std::unique_ptr<VulkanDescriptorSet>& descriptor_set,
        const size_t& binding,
        const size_t& dst_array_element
    ) {
        VkDescriptorBufferInfo buffer_info{};
        buffer_info.buffer = buffer.get_vulkan_buffer();
        buffer_info.offset = 0;
        buffer_info.range = buffer.get_size();

        VkWriteDescriptorSet descriptor_write{};
        descriptor_write.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;

        descriptor_write.dstSet = descriptor_set->backend;
        descriptor_write.dstBinding = binding;
        descriptor_write.dstArrayElement = dst_array_element;
        // Todo, remember that this mean \/
        // Todo THIS IS A HANDLE, and handle counter should work per shader binding, not a cpu binding thing

        descriptor_write.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
        descriptor_write.descriptorCount = 1;
        descriptor_write.pBufferInfo = &buffer_info;

        descriptor_write.pImageInfo = nullptr; // Optional
        descriptor_write.pTexelBufferView = nullptr; // Optional

        vkUpdateDescriptorSets(device, 1, &descriptor_write, 0, nullptr);
    }

    void VulkanDevice::update_descriptor_set(
        IVulkanSampler& sampler,
        IVulkanImageView& view,
        std::unique_ptr<VulkanDescriptorSet>& descriptor_set,
        const size_t& binding,
        const size_t& dst_array_element
    ) {
        VkDescriptorImageInfo image_info{};
        image_info.sampler = sampler.get_vulkan_image_sampler();
        image_info.imageView = view.get_vulkan_image_view();
        image_info.imageLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL; // Todo, remove this hard coded cringe

        VkWriteDescriptorSet descriptor_write{};
        descriptor_write.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;

        descriptor_write.dstSet = descriptor_set->backend;
        descriptor_write.dstBinding = binding;
        descriptor_write.dstArrayElement = dst_array_element; // Todo THIS IS A HANDLE, and handle counter should work per shader binding, not a cpu binding thing

        descriptor_write.descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
        descriptor_write.descriptorCount = 1;
        // descriptorWrite.pBufferInfo = &buffer_info;
        descriptor_write.pImageInfo = &image_info;

        // descriptorWrite.pImageInfo = nullptr; // Optional
        descriptor_write.pTexelBufferView = nullptr; // Optional

        vkUpdateDescriptorSets(device, 1, &descriptor_write, 0, nullptr);
    }

    /*
    void VulkanDevice::update_descriptor_sets(
        const std::vector<std::unique_ptr<VulkanBuffer>>& buffers,
        std::vector<std::unique_ptr<VulkanDescriptorSet>>& descriptor_sets,
        const size_t& binding,
        const std::vector<size_t>& dst_array_elements
    ) {
        if(buffers.size() != dst_array_elements.size()) {
            LOG_ERROR("Buffer an dst_array_elements count is not matching");
            throw std::runtime_error("buffer an dst_array_elements count is not matching");
        }

        for(size_t i = 0; i < dst_array_elements.size(); ++i) {
            auto& buffer = buffers[i];
            auto& dst_array_element = dst_array_elements[i];
            auto& descriptor_set = descriptor_sets[i];

            update_descriptor_set(buffer, descriptor_set, binding, dst_array_element);
        }
    }

    void VulkanDevice::update_descriptor_sets(
        const std::vector<std::unique_ptr<VulkanBufferMemory>>& tuples,
        std::vector<std::unique_ptr<VulkanDescriptorSet>>& descriptor_sets,
        const size_t& binding,
        const std::vector<size_t>& dst_array_elements
    ) {
        if(tuples.size() != dst_array_elements.size()) {
            LOG_ERROR("Buffer an dst_array_elements count is not matching");
            throw std::runtime_error("buffer an dst_array_elements count is not matching");
        }

        for(size_t i = 0; i < dst_array_elements.size(); ++i) {
            const auto& buffer = tuples[i]->buffer;
            const auto& dst_array_element = dst_array_elements[i];
            auto& descriptor_set = descriptor_sets[i];

            update_descriptor_set(buffer, descriptor_set, binding, dst_array_element);
        }
    }

    void VulkanDevice::update_descriptor_sets(
        const std::unique_ptr<VulkanSampler>& sampler,
        const std::unique_ptr<VulkanImageView>& view,
        std::vector<std::unique_ptr<VulkanDescriptorSet>>& descriptor_sets,
        const size_t& binding,
        const std::vector<size_t>& dst_array_elements
    ) {
        for(size_t i = 0; i < dst_array_elements.size(); ++i) {
            auto& dst_array_element = dst_array_elements[i];
            auto& descriptor_set = descriptor_sets[i];

            update_descriptor_set(sampler, view, descriptor_set, binding, dst_array_element);
        }
    }
    */

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

    std::unique_ptr<VulkanDeviceMemory> VulkanDevice::create_device_memory(
        VkMemoryRequirements requirements,
        VkMemoryPropertyFlags local_properties
    ) {
        return std::make_unique<VulkanDeviceMemory>(*this, requirements, local_properties);
    }

    std::unique_ptr<VulkanBufferMemory> VulkanDevice::create_buffer_memory(
        const size_t& size,
        VulkanBufferInfo buffer_info
    ) {
        return std::make_unique<VulkanBufferMemory>(*this, size, buffer_info);
    }

    std::vector<std::unique_ptr<VulkanBuffer>> VulkanDevice::create_buffers(
        const size_t& size,
        const size_t& count,
        VulkanBufferInfo buffer_info
    ) {
        auto buffers = std::vector<std::unique_ptr<VulkanBuffer>> {};
        buffers.reserve(count);

        for(size_t i = 0; i < count; ++i)
            buffers.push_back(std::make_unique<VulkanBuffer>(*this, size, buffer_info));

        return buffers;
    }

    std::vector<std::unique_ptr<VulkanBufferMemory>> VulkanDevice::create_buffer_memorys(
        const size_t& size,
        const size_t& count,
        VulkanBufferInfo buffer_info
    ) {
        auto tuples = std::vector<std::unique_ptr<VulkanBufferMemory>> {};
        tuples.reserve(count);

        for(size_t i = 0; i < count; ++i)
            tuples.emplace_back(create_buffer_memory(size, buffer_info));

        return tuples;
    }

    std::unique_ptr<VulkanImage> VulkanDevice::create_image(VkFormat format, VkExtent3D extent, VulkanImageInfo image_info) {
        return std::make_unique<VulkanImage>(*this, format, extent, image_info);;
    }

    std::unique_ptr<VulkanImageMemory> VulkanDevice::create_image_memory(VkFormat format, VkExtent3D extent, VulkanImageInfo image_info) {
        auto image = create_image(format, extent, image_info);

        auto req = image->get_memory_requirements();

        auto memory = create_device_memory(req, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);
        memory->bind_image_memory(image);

        return std::make_unique<VulkanImageMemory>(image, memory);
    }

    // Todo Why this function is public ?, and probably could be static
    std::unique_ptr<VulkanImage> VulkanDevice::create_image(VkImage& image) {
        return std::make_unique<VulkanImage>(*this, image);;
    }

    std::unique_ptr<VulkanSampler> VulkanDevice::create_sampler() {
        return std::make_unique<VulkanSampler>(*this);;
    }

    std::unique_ptr<VulkanImageView> VulkanDevice::create_image_view(
        VulkanImage& image,
        const VkFormat& image_format,
        VulkanImageViewInfo image_view_info
    ) {
        return std::make_unique<VulkanImageView>(*this, image, image_format, image_view_info);;
    }

    std::unique_ptr<VulkanDepthImage> VulkanDevice::create_depth_image_tuple(VkExtent3D extent) {
        return std::make_unique<VulkanDepthImage>(*this, extent);
    }

    std::vector<std::unique_ptr<VulkanDepthImage>> VulkanDevice::create_depth_image_tuples(VkExtent3D extent, const size_t& count) {
        auto tuples = std::vector<std::unique_ptr<VulkanDepthImage>> {};
        tuples.reserve(count);

        for(size_t i = 0; i < count; ++i)
            tuples.push_back(create_depth_image_tuple(extent));

        return tuples;
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

    std::unique_ptr<VulkanTexture> VulkanDevice::create_texture(
        const std::string& file_path
    ) {
        auto raw = assets::Image<ColorRGBA>::load_from_file(file_path);

        return std::make_unique<VulkanTexture>(*this, raw);
    }

    std::unique_ptr<VulkanTexture> VulkanDevice::create_texture(
        VkExtent3D extent,
        VkFormat image_format
    ) {
        return std::make_unique<VulkanTexture>(*this, extent, image_format);;
    }

    std::vector<std::unique_ptr<VulkanTexture>> VulkanDevice::create_textures(
        VkExtent3D extent,
        VkFormat image_format,
        const size_t& count
    ) {
        auto textures = std::vector<std::unique_ptr<VulkanTexture>> {};
        textures.reserve(3);

        for(size_t i = 0; i < count; ++i)
            textures.push_back(create_texture(extent, image_format));

        return textures;
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
