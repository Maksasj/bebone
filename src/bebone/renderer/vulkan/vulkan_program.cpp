#include "vulkan_program.h"

namespace bebone::renderer {
    using namespace bebone::gfx;

    VulkanProgram::VulkanProgram(
        const std::shared_ptr<VulkanPipeline>& pipeline,
        const std::shared_ptr<VulkanPipelineLayout>& pipeline_layout
    ) : pipeline(pipeline), pipeline_layout(pipeline_layout) {

    }

    void VulkanProgram::bind(ICommandEncoder* encoder) {
        auto vulkan_encoder = static_cast<VulkanCommandEncoder*>(encoder);

        auto cmd = vulkan_encoder->get_command_buffer();

        cmd->bind_pipeline(pipeline);
    }

    std::shared_ptr<VulkanPipeline> VulkanProgram::get_pipeline() {
        return pipeline;
    }

    std::shared_ptr<VulkanPipelineLayout> VulkanProgram::get_pipeline_layout() {
        return pipeline_layout;
    }
}
