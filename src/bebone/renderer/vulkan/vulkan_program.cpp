#include "vulkan_program.h"

namespace bebone::renderer {
    using namespace bebone::gfx;

    VulkanProgram::VulkanProgram(const VulkanManagedPipelineTuple& pipeline) : pipeline(pipeline) {

    }

    void VulkanProgram::bind(ICommandEncoder* encoder) {
        auto vulkan_encoder = static_cast<VulkanCommandEncoder*>(encoder);

        auto cmd = vulkan_encoder->get_command_buffer();
        auto frame = vulkan_encoder->get_frame();

        cmd->bind_managed_pipeline(pipeline, frame);
    }

    const VulkanManagedPipelineTuple& VulkanProgram::get_pipeline() const {
        return pipeline;
    }
}
