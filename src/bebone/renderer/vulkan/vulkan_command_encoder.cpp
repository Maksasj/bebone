#include "vulkan_command_encoder.h"

namespace bebone::renderer {
    using namespace bebone::gfx;

    VulkanCommandEncoder::VulkanCommandEncoder(
        const std::shared_ptr<VulkanSwapChain>& swap_chain,
        const std::shared_ptr<VulkanCommandBuffer>& command_buffer,
        const size_t& frame
    ) : swap_chain(swap_chain), command_buffer(command_buffer), frame(frame) {

    }

    std::shared_ptr<VulkanSwapChain>& VulkanCommandEncoder::get_swap_chain() {
        return swap_chain;
    }

    std::shared_ptr<VulkanCommandBuffer>& VulkanCommandEncoder::get_command_buffer() {
        return command_buffer;
    }

    const size_t& VulkanCommandEncoder::get_frame() const {
        return frame;
    }
}
