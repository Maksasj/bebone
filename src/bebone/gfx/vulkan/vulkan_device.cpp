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

    VulkanDevice::VulkanDevice(VulkanInstance& instance, VulkanWindow &window) {
        window.create_window_surface(instance.get_instance(), &surface);

        pick_physical_device(instance);
        create_logical_device();
    }

    void VulkanDevice::pick_physical_device(VulkanInstance& instance) {
        auto chooser = VulkanDeviceChooser();

        physical_device = chooser.get_physical_device(instance, surface);

        vkGetPhysicalDeviceProperties(physical_device, &properties);

        std::cout << "physical device: " << properties.deviceName << std::endl;
    }

    std::shared_ptr<VulkanDescriptorPool> VulkanDevice::create_descriptor_pool() {
        auto descriptor_pool = std::make_shared<VulkanDescriptorPool>(*this);

        child_objects.push_back(descriptor_pool);

        return descriptor_pool;
    }

    // Todo why there is a vector ?
    std::vector<std::shared_ptr<VulkanDescriptorSetLayout>> VulkanDevice::create_descriptor_set_layouts(
        const std::vector<VulkanDescriptorSetLayoutBinding>& bindings
    ) {
        auto descriptor_set_layout = std::make_shared<VulkanDescriptorSetLayout>(*this, bindings);

        child_objects.push_back(descriptor_set_layout);

        return { descriptor_set_layout };
    }

    std::shared_ptr<VulkanRenderTarget> VulkanDevice::create_render_target(
        std::vector<VulkanSwapChainImageTuple>& images,
        VkFormat image_format,
        VkExtent2D extent
    ) {
        return std::make_unique<VulkanRenderTarget>(*this, images, image_format, extent);
    }

    std::shared_ptr<VulkanSwapChain> VulkanDevice::create_swap_chain(std::shared_ptr<Window> &window) {
        auto swap_chain = std::make_shared<VulkanSwapChain>(*this, VkExtent2D { static_cast<uint32_t>(window->get_width()), static_cast<uint32_t>(window->get_height()) });

        child_objects.push_back(swap_chain);

        return swap_chain;
    }

    std::shared_ptr<VulkanPipelineLayout> VulkanDevice::create_pipeline_layout(const std::vector<std::shared_ptr<VulkanDescriptorSetLayout>>& layouts, const std::vector<VulkanConstRange>& constant_Ranges) {
        auto pipeline_layout = std::make_shared<VulkanPipelineLayout>(*this, layouts, constant_Ranges);

        child_objects.push_back(pipeline_layout);

        return pipeline_layout;
    }

    std::shared_ptr<VulkanCommandBufferPool> VulkanDevice::create_command_buffer_pool() {
        auto command_buffer_pool = std::make_shared<VulkanCommandBufferPool>(*this);

        child_objects.push_back(command_buffer_pool);

        return command_buffer_pool;
    }

    std::shared_ptr<VulkanDeviceMemory> VulkanDevice::create_device_memory(
        VkMemoryRequirements requirements,
        VkMemoryPropertyFlags properties
    ) {
        auto device_memory = std::make_shared<VulkanDeviceMemory>(*this, requirements, properties);

        child_objects.push_back(device_memory);

        return device_memory;
    }

    std::shared_ptr<VulkanBuffer> VulkanDevice::create_buffer(
        const size_t& size,
        VulkanBufferInfo buffer_info
    ) {
        auto buffer = std::make_shared<VulkanBuffer>(*this, size, buffer_info);

        child_objects.push_back(buffer);

        return buffer;
    }

    VulkanBufferMemoryTuple VulkanDevice::create_buffer_memory(
        const size_t& size,
        VulkanBufferInfo buffer_info
    ) {
        auto buffer = create_buffer(size, buffer_info);

        auto requirements = buffer->get_memory_requirements(*this);

        auto memory = create_device_memory(requirements, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT); // Todo this should be configurable
        memory->bind_buffer_memory(*this, buffer);

        return { buffer, memory };
    }

    std::vector<std::shared_ptr<VulkanBuffer>> VulkanDevice::create_buffers(
        const size_t& size,
        const size_t& count,
        VulkanBufferInfo buffer_info
    ) {
        auto buffers = std::vector<std::shared_ptr<VulkanBuffer>> {};
        buffers.reserve(count);

        for(size_t i = 0; i < count; ++i)
            buffers.push_back(create_buffer(size, buffer_info));

        return buffers;
    }

    std::vector<VulkanBufferMemoryTuple> VulkanDevice::create_buffer_memorys(
        const size_t& size,
        const size_t& count,
        VulkanBufferInfo buffer_info
    ) {
        auto tuples = std::vector<VulkanBufferMemoryTuple> {};
        tuples.reserve(count);

        for(size_t i = 0; i < count; ++i)
            tuples.emplace_back(create_buffer_memory(size, buffer_info));

        return tuples;
    }

    std::shared_ptr<VulkanImage> VulkanDevice::create_image(VkFormat format, VkExtent3D extent, VulkanImageInfo image_info) {
        auto image = std::make_shared<VulkanImage>(*this, format, extent, image_info);

        child_objects.push_back(image);

        return image;
    }

    VulkanImageMemoryTuple VulkanDevice::create_image_memory(VkFormat format, VkExtent3D extent, VulkanImageInfo image_info) {
        auto image = std::make_shared<VulkanImage>(*this, format, extent, image_info);

        auto req = image->get_memory_requirements(*this);

        auto memory = create_device_memory(req, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);
        memory->bind_image_memory(*this, image);

        return make_tuple(image, memory);
    }

    // Todo Why this function is public ?, and probably could be static
    std::shared_ptr<VulkanImage> VulkanDevice::create_image(VkImage& image) {
        auto im = std::make_shared<VulkanImage>(image);

        // This image provided by implementation so, no need in clearing

        return im;
    }

    std::shared_ptr<VulkanSampler> VulkanDevice::create_sampler() {
        auto sampler = std::make_shared<VulkanSampler>(*this);

        child_objects.push_back(sampler);

        return sampler;
    }

    std::shared_ptr<VulkanImageView> VulkanDevice::create_image_view(
        VulkanImage& image,
        const VkFormat& image_format,
        VulkanImageViewInfo image_view_info
    ) {
        auto view = std::make_shared<VulkanImageView>(*this, image, image_format, image_view_info);

        child_objects.push_back(view);

        return view;
    }

    std::shared_ptr<VulkanPipeline> VulkanDevice::create_pipeline(
        std::shared_ptr<VulkanSwapChain>& swap_chain,
        std::shared_ptr<VulkanPipelineLayout>& pipeline_layout,
        std::vector<std::shared_ptr<VulkanShaderModule>> shader_modules,
        VulkanPipelineConfig config_info
    ) {
        auto pipeline = std::make_shared<VulkanPipeline>(*this, swap_chain, pipeline_layout, shader_modules, config_info);

        child_objects.push_back(pipeline);

        return pipeline;
    }

    std::shared_ptr<VulkanShaderModule> VulkanDevice::create_shader_module(const std::string& file_path, const ShaderType& type) {
        auto shader_compiler = SpirVShaderCompiler();

        shader_compiler.add_shader_source(ShaderSource(
            vulkan_device_read_file(file_path),
            type
        ));

        auto shadeCode = shader_compiler.compile(type);
        auto shader = std::make_shared<VulkanShaderModule>(*this, shadeCode);

        child_objects.push_back(shader);

        return shader;
    }

    std::shared_ptr<VulkanTexture> VulkanDevice::create_texture(
        std::shared_ptr<VulkanCommandBufferPool>& command_buffer_pool,
        const std::string& file_path
    ) {
        auto raw = assets::Image<ColorRGBA>::load_from_file(file_path);
        auto texture = std::make_shared<VulkanTexture>(*this, command_buffer_pool, raw);

        child_objects.push_back(texture);

        return texture;
    }

    std::shared_ptr<VulkanPipelineManager> VulkanDevice::create_pipeline_manager() {
        auto pipeline_manager = std::make_shared<VulkanPipelineManager>(*this);

        child_objects.push_back(pipeline_manager);

        return pipeline_manager;
    }

    void VulkanDevice::create_logical_device() {
        auto indices = VulkanDeviceChooser::find_queue_families(physical_device, surface);

        auto unique_queue_families = std::set<uint32_t> { indices.graphics_family, indices.present_family };

        auto queue_create_infos = std::vector<VkDeviceQueueCreateInfo> {};
        queue_create_infos.reserve(unique_queue_families.size());

        float queuePriority = 1.0f;

        for(const auto& queueFamily : unique_queue_families) {
            VkDeviceQueueCreateInfo queue_create_info = {};

            queue_create_info.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
            queue_create_info.queueFamilyIndex = queueFamily;
            queue_create_info.queueCount = 1;
            queue_create_info.pQueuePriorities = &queuePriority;

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

        if(vkCreateDevice(physical_device, &create_info, nullptr, &device) != VK_SUCCESS)
            throw std::runtime_error("failed to create logical device!");

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

        throw std::runtime_error("failed to find supported format!");
    }

    uint32_t VulkanDevice::find_memory_type(uint32_t type_filter, VkMemoryPropertyFlags m_properties) {
        VkPhysicalDeviceMemoryProperties mem_properties;
        vkGetPhysicalDeviceMemoryProperties(physical_device, &mem_properties);

        for(uint32_t i = 0; i < mem_properties.memoryTypeCount; i++) {
            if((type_filter & (1 << i)) && (mem_properties.memoryTypes[i].propertyFlags & m_properties) == m_properties)
                return i;
        }

        throw std::runtime_error("failed to find suitable memory type!");
    }

    void VulkanDevice::wait_idle() {
        vkDeviceWaitIdle(device);
    }

    void VulkanDevice::collect_garbage() {
        child_objects.erase(std::remove_if(child_objects.begin(), child_objects.end(), [](shared_ptr<VulkanApi>& child) {
            return child->is_destroyed();
        }), child_objects.end());
    }

    void VulkanDevice::destroy(VulkanInstance& instance) {
        wait_idle();

        collect_garbage();

        for(auto& child : child_objects) {
            if(!child->is_destroyed()) {
                destroy_all(child);
            }
        }

        vkDestroyDevice(device, nullptr);
        vkDestroySurfaceKHR(instance.get_instance(), surface, nullptr);
    }

    VkFormat VulkanDevice::find_depth_format() {
        return find_supported_format(
            {VK_FORMAT_D32_SFLOAT, VK_FORMAT_D32_SFLOAT_S8_UINT, VK_FORMAT_D24_UNORM_S8_UINT},
            VK_IMAGE_TILING_OPTIMAL,
            VK_FORMAT_FEATURE_DEPTH_STENCIL_ATTACHMENT_BIT);
    }
}
