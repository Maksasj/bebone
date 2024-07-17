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

    void VulkanProgramManager::bind_texture(std::shared_ptr<VulkanTexture>& texture) {
        texture->handle = pipeline_manager->bind_texture(device, texture->get_texture());
    }

    std::shared_ptr<VulkanPipelineManager> VulkanProgramManager::get_pipeline_manager() const {
        return pipeline_manager;
    }
}
