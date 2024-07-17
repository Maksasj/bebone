#include "vulkan_pipeline_manager.h"

#include <utility>

#include "vulkan_device.h"
#include "vulkan_descriptor_pool.h"
#include "vulkan_descriptor_set_layout.h"
#include "vulkan_descriptor_set_layout_binding.h"

namespace bebone::gfx {
    // Todo, move this
    std::string vulkan_device_read_file(const std::string& path) {
        std::ifstream file(path);
        std::stringstream ss;

        ss << file.rdbuf();

        return ss.str();
    }

    VulkanPipelineManager::VulkanPipelineManager(VulkanDevice& device) : bindless_uniforms_index(0), bindless_storage_index(0), bindless_samplers_index(0) {
        descriptor_pool = device.create_descriptor_pool();

        static constexpr u32 uniform_binding = 0;
        static constexpr u32 storage_binding = 1;
        static constexpr u32 texture_binding = 2;

        const std::vector<VulkanDescriptorSetLayoutBinding> bindless_bindings = {
            { Uniform, uniform_binding },
            { Storage, storage_binding },
            { Sampler, texture_binding }
        };

        // Creating bindless descriptor set layout
        bindless_descriptor_set_layout = device.create_descriptor_set_layout(bindless_bindings);
        bindless_descriptor_set = descriptor_pool->create_descriptor(device, bindless_descriptor_set_layout);
    }

    VulkanManagedPipelineTuple VulkanPipelineManager::create_pipeline(
        std::shared_ptr<VulkanDevice>& device,
        const std::shared_ptr<VulkanRenderPass>& render_pass,
        std::shared_ptr<VulkanShaderModule> vertex_shader_module,
        std::shared_ptr<VulkanShaderModule> fragment_shader_module,
        const std::vector<VulkanConstRange>& constant_ranges,
        VulkanPipelineConfig config_info
    ) {
        auto pipeline_layout = device->create_pipeline_layout({ bindless_descriptor_set_layout }, constant_ranges);
        auto pipeline = device->create_pipeline(render_pass, pipeline_layout, { vertex_shader_module, fragment_shader_module }, std::move(config_info));

        return { pipeline, pipeline_layout };
    }

    // Todo, actually swap chain is not needed there
    VulkanManagedPipelineTuple VulkanPipelineManager::create_pipeline(
        std::shared_ptr<VulkanDevice>& device,
        const std::shared_ptr<VulkanRenderPass>& render_pass,
        const std::string& vertex_shader_file_path,
        const std::string& fragment_shader_file_path,
        const std::vector<VulkanConstRange>& constant_ranges,
        VulkanPipelineConfig config_info
    ) {
        auto vert_shader_module = device->create_shader_module(vulkan_device_read_file(vertex_shader_file_path), VertexShader);
        auto frag_shader_module = device->create_shader_module(vulkan_device_read_file(fragment_shader_file_path), FragmentShader);

        auto pipeline = create_pipeline(device, render_pass, vert_shader_module, frag_shader_module, constant_ranges, config_info);

        device->destroy_all(vert_shader_module, frag_shader_module);
        device->collect_garbage();

        return pipeline;
    }

    const std::shared_ptr<VulkanDescriptorSet>& VulkanPipelineManager::get_descriptor_set() const {
        return bindless_descriptor_set;
    }

    const std::shared_ptr<VulkanDescriptorSetLayout>& VulkanPipelineManager::get_descriptor_set_layout() const {
        return bindless_descriptor_set_layout;
    }

    void VulkanPipelineManager::destroy(VulkanDevice& device) {
        if(is_destroyed())
            return;

        bindless_descriptor_set_layout->destroy(device);
        bindless_descriptor_set->destroy(device);
        descriptor_pool->destroy(device);

        mark_destroyed();
    }
}
