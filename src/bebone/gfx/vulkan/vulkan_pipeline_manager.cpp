#include "vulkan_pipeline_manager.h"

#include <utility>

#include "vulkan_device.h"
#include "vulkan_pipeline_layout.h"
#include "vulkan_descriptor_pool.h"
#include "vulkan_descriptor_set_layout.h"
#include "vulkan_descriptor_set_layout_binding.h"
#include "vulkan_const_range.h"

namespace bebone::gfx {
    VulkanPipelineManager::VulkanPipelineManager(VulkanDevice& device) : device(device), bindless_uniforms_index(0), bindless_storage_index(0), bindless_samplers_index(0) {
        descriptor_pool = device.create_descriptor_pool();

        const std::vector<VulkanDescriptorSetLayoutBinding> bindless_bindings = {
            { Uniform, uniform_binding },
            // { Storage, storage_binding }, Todo
            { Sampler, texture_binding }
        };

        // Creating bindless descriptor set layout
        bindless_descriptor_set_layout = device.create_descriptor_set_layout(bindless_bindings);
        bindless_descriptor_set = descriptor_pool->create_descriptor(bindless_descriptor_set_layout);

        // Creating bindless pipeline layout
        const auto constant_ranges = { VulkanConstRange(const_ranges_size, 0) };

        bindless_pipeline_layout = device.create_pipeline_layout({ bindless_descriptor_set_layout }, constant_ranges);

        std::ignore = bindless_storage_index; // Todo

        LOG_TRACE("Created Vulkan pipeline manager");
    }

    VulkanPipelineManager::~VulkanPipelineManager() {
        // bindless_pipeline_layout->destroy(device);
        // bindless_descriptor_set_layout->destroy(device);
        // bindless_descriptor_set->destroy(device);
        // descriptor_pool->destroy(device);

        LOG_DEBUG("Destroyed Vulkan pipeline manager");
    }

    std::shared_ptr<VulkanPipeline> VulkanPipelineManager::create_pipeline(
        std::shared_ptr<VulkanDevice>& device,
        const std::unique_ptr<VulkanRenderPass>& render_pass,
        std::unique_ptr<VulkanShaderModule> vertex_shader_module,
        std::unique_ptr<VulkanShaderModule> fragment_shader_module,
        VulkanPipelineConfig config_info
    )
    {
        std::vector<unique_ptr<VulkanShaderModule>> shader_modules;
        shader_modules.push_back(std::move(vertex_shader_module));
        shader_modules.push_back(std::move(fragment_shader_module));

        return device->create_pipeline(render_pass, *bindless_pipeline_layout, shader_modules, std::move(config_info));;
    }

    std::shared_ptr<VulkanPipeline> VulkanPipelineManager::create_pipeline(
        std::shared_ptr<VulkanDevice>& device,
        const std::unique_ptr<VulkanRenderPass>& render_pass,
        const std::string& vertex_shader_file_path,
        const std::string& fragment_shader_file_path,
        VulkanPipelineConfig config_info
    ) {
        auto vert_shader_module = device->create_shader_module(utils_read_file(vertex_shader_file_path), ShaderType::VertexShader);
        auto frag_shader_module = device->create_shader_module(utils_read_file(fragment_shader_file_path), ShaderType::FragmentShader);

        auto pipeline = create_pipeline(device, render_pass, std::move(vert_shader_module), std::move(frag_shader_module), config_info);

        // device->destroy_all(vert_shader_module, frag_shader_module);
        // device->collect_garbage();

        return pipeline;
    }

    VulkanBindlessTextureHandle VulkanPipelineManager::bind_texture(
        std::shared_ptr<VulkanDevice>& device,
        std::shared_ptr<VulkanTextureTuple>& texture
    ) {
        const auto handle = bindless_samplers_index;

        device->update_descriptor_set(texture->sampler, texture->view, bindless_descriptor_set, texture_binding, bindless_samplers_index);
        ++bindless_samplers_index;

        return static_cast<VulkanBindlessTextureHandle>(handle);
    }

    std::vector<VulkanBindlessTextureHandle> VulkanPipelineManager::bind_textures(
        std::shared_ptr<VulkanDevice>& device,
        std::vector<std::shared_ptr<VulkanTextureTuple>>& textures
    ) {
        auto handles = std::vector<VulkanBindlessTextureHandle> {};
        handles.reserve(textures.size());

        for(auto& texture : textures)
            handles.push_back(bind_texture(device, texture));

        return handles;
    }

    VulkanBindlessTextureHandle VulkanPipelineManager::bind_attachment(
        std::shared_ptr<VulkanDevice>& device,
        std::shared_ptr<IVulkanAttachment>& attachment
    ) {
        // Todo
        if(!attachment->get_sampler().has_value())
            LOG_WARNING("Sampler does not have any value");

        // Todo
        if(!attachment->get_view().has_value())
            LOG_WARNING("View does not have any value");

        // Todo
        auto sampler = attachment->get_sampler().value();
        auto view = attachment->get_view().value();

        const auto handle = bindless_samplers_index;

        device->update_descriptor_set(sampler, view, bindless_descriptor_set, texture_binding, bindless_samplers_index);
        ++bindless_samplers_index;

        return static_cast<VulkanBindlessTextureHandle>(handle);
    }

    std::vector<VulkanBindlessTextureHandle> VulkanPipelineManager::bind_attachments(
        std::shared_ptr<VulkanDevice>& device,
        std::vector<std::shared_ptr<IVulkanAttachment>>& attachments
    ) {
        auto handles = std::vector<VulkanBindlessTextureHandle> {};
        handles.reserve(attachments.size());

        for(auto& attachment : attachments)
            handles.push_back(bind_attachment(device, attachment));

        return handles;
    }

    VulkanBindlessBufferHandle VulkanPipelineManager::bind_uniform_buffer(
        std::shared_ptr<VulkanDevice>& device,
        const std::shared_ptr<VulkanBufferMemoryTuple>& buffer
    ) {
        const auto handle = bindless_uniforms_index;

        device->update_descriptor_set(buffer->buffer, bindless_descriptor_set, uniform_binding, bindless_uniforms_index);
        ++bindless_uniforms_index;

        return static_cast<VulkanBindlessBufferHandle>(handle);
    }

    std::vector<VulkanBindlessBufferHandle> VulkanPipelineManager::bind_uniform_buffers(
        std::shared_ptr<VulkanDevice>& device,
        const std::vector<std::shared_ptr<VulkanBufferMemoryTuple>>& buffers
    ) {
        auto handles = std::vector<VulkanBindlessBufferHandle> {};
        handles.reserve(buffers.size());

        for(auto& buffer : buffers)
            handles.push_back(bind_uniform_buffer(device, buffer));

        return handles;
    }

    const std::shared_ptr<VulkanDescriptorSet>& VulkanPipelineManager::get_descriptor_set() const {
        return bindless_descriptor_set;
    }

    const std::shared_ptr<VulkanDescriptorSetLayout>& VulkanPipelineManager::get_descriptor_set_layout() const {
        return bindless_descriptor_set_layout;
    }

    const std::shared_ptr<VulkanPipelineLayout>& VulkanPipelineManager::get_pipeline_layout() const {
        return bindless_pipeline_layout;
    }

    /*
    void VulkanPipelineManager::destroy(VulkanDevice& device) {
        if(is_destroyed())
            return;

        bindless_pipeline_layout->destroy(device);
        bindless_descriptor_set_layout->destroy(device);
        bindless_descriptor_set->destroy(device);
        descriptor_pool->destroy(device);

        LOG_TRACE("Destroyed Vulkan pipeline manager");

        mark_destroyed();
    }
    */
}
