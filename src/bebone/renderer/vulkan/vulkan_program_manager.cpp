#include "vulkan_program_manager.h"

namespace bebone::renderer {
    VulkanProgramManager::VulkanProgramManager(const std::shared_ptr<VulkanDevice>& device) : device(device) {
        pipeline_manager = device->create_pipeline_manager();
    }

    std::shared_ptr<VulkanProgram> VulkanProgramManager::create_program(std::shared_ptr<VulkanPipeline>& pipeline) {
        auto program = std::make_shared<VulkanProgram>(pipeline);
        programs.push_back(program);
        return program;
    }

    void VulkanProgramManager::bind_texture(std::shared_ptr<VulkanTextureImpl>& texture) {
        texture->handle = pipeline_manager->bind_texture(device, texture->get_texture());
    }

    std::shared_ptr<VulkanPipelineManager> VulkanProgramManager::get_pipeline_manager() const {
        return pipeline_manager;
    }

    const std::shared_ptr<VulkanDescriptorSet>& VulkanProgramManager::get_descriptor_set() const {
        return pipeline_manager->get_descriptor_set();
    }

    const std::shared_ptr<VulkanDescriptorSetLayout>& VulkanProgramManager::get_descriptor_set_layout() const {
        return pipeline_manager->get_descriptor_set_layout();
    }

    const std::shared_ptr<VulkanPipelineLayout>& VulkanProgramManager::get_pipeline_layout() const {
        return pipeline_manager->get_pipeline_layout();
    }
}
