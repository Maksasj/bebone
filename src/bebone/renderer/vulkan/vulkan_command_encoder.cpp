#include "vulkan_command_encoder.h"

namespace bebone::renderer {
    using namespace bebone::gfx;

    VulkanCommandEncoder::VulkanCommandEncoder(const std::shared_ptr<VulkanCommandBuffer>& command_buffer) : command_buffer(command_buffer) {

    }

    std::shared_ptr<VulkanCommandBuffer>& VulkanCommandEncoder::get_command_buffer() {
        return command_buffer;
    }
}
