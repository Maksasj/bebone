#include "vulkan_program_manager.h"

const auto vulkan_present_pass_vertex_descriptions = bebone::gfx::VulkanPipelineVertexInputStateTuple {
    .binding_descriptions = {
        { 0, sizeof(bebone::renderer::Vertex), VK_VERTEX_INPUT_RATE_VERTEX }
    },
    .attribute_descriptions = {
        { 0, 0, VK_FORMAT_R32G32B32_SFLOAT, offsetof(bebone::renderer::Vertex, position) },
        { 1, 0, VK_FORMAT_R32G32B32_SFLOAT, offsetof(bebone::renderer::Vertex, normal) },
        { 2, 0, VK_FORMAT_R32G32_SFLOAT,    offsetof(bebone::renderer::Vertex, texcoord) },
    }
};

namespace bebone::renderer {
    VulkanProgramManager::VulkanProgramManager(const std::shared_ptr<VulkanDevice>& device) : device(device) {
        pipeline_manager = device->create_pipeline_manager();
    }

    std::shared_ptr<IProgram> VulkanProgramManager::create_program(const std::string& vertex_shader_code, const std::string& fragment_shader_code) override {
        auto vert_shader_module = device->create_shader_module(vertex_shader_code, VertexShader);
        auto frag_shader_module = device->create_shader_module(fragment_shader_code, FragmentShader);

        // Create pipeline
        auto pipeline = pipeline_manager->create_pipeline(
            device, render_pass, vert_shader_module, frag_shader_module,
            { .vertex_input_state = { .vertex_descriptions = vulkan_present_pass_vertex_descriptions } }
        );

        // Delete shader modules and clear memory
        device->destroy_all(vert_shader_module, frag_shader_module);
        device->collect_garbage();

        return std::make_shared<VulkanProgram>(pipeline, pipeline_manager->get_pipeline_layout());
    }

    void VulkanProgramManager::bind_texture(std::shared_ptr<VulkanTextureImpl>& texture) {
        texture->handle = pipeline_manager->bind_texture(device, texture->get_texture());
    }

    std::shared_ptr<VulkanPipelineManager> VulkanProgramManager::get_pipeline_manager() const {
        return pipeline_manager;
    }

    std::shared_ptr<VulkanDescriptorSet> VulkanProgramManager::get_descriptor_set() const {
        return pipeline_manager->get_descriptor_set();
    }

    std::shared_ptr<VulkanDescriptorSetLayout> VulkanProgramManager::get_descriptor_set_layout() const {
        return pipeline_manager->get_descriptor_set_layout();
    }

    std::shared_ptr<VulkanPipelineLayout> VulkanProgramManager::get_pipeline_layout() const {
        return pipeline_manager->get_pipeline_layout();
    }
}
