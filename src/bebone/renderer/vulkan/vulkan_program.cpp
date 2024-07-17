#include "vulkan_program.h"

namespace bebone::renderer {
    using namespace bebone::gfx;

    VulkanProgram::VulkanProgram(const std::shared_ptr<VulkanPipeline>& pipeline) : pipeline(pipeline) {

    }

    void VulkanProgram::bind(ICommandEncoder* encoder) {
        auto vulkan_encoder = static_cast<VulkanCommandEncoder*>(encoder);

        auto cmd = vulkan_encoder->get_command_buffer();

        cmd->bind_pipeline(pipeline);
    }

        std::shared_ptr<VulkanPipeline>& VulkanProgram::get_pipeline() {
        return pipeline;
    }
}
