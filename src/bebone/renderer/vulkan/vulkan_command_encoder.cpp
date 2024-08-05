#include "vulkan_command_encoder.h"
#include "../iprogram.h"
#include "vulkan_program.h"

namespace bebone::renderer {
    using namespace bebone::gfx;

    VulkanCommandEncoder::VulkanCommandEncoder(
        const std::shared_ptr<VulkanDevice>& device,
        const std::shared_ptr<VulkanSwapChain>& swap_chain,
        const std::shared_ptr<VulkanCommandBuffer>& command_buffer,
        const size_t& frame
    ) : device(device), swap_chain(swap_chain), command_buffer(command_buffer), frame(frame) {

    }

    void VulkanCommandEncoder::begin_render_pass(const std::shared_ptr<IRenderTarget>& render_target, const std::shared_ptr<IPassImpl>& pass) {
        auto vulkan_pass = static_pointer_cast<VulkanPassImpl>(pass)->get_vulkan_pass();
        command_buffer->begin_render_pass(todo, vulkan_pass)
    }

    void VulkanCommandEncoder::end_render_pass() {
        command_buffer->end_render_pass();
    }

    void VulkanCommandEncoder::set_viewport(const Vec2i& viewport) {
        command_buffer->set_viewport(viewport);
    }

    void VulkanCommandEncoder::bind_program(const std::shared_ptr<IProgram>& program) {
        program->bind(this);
    }

    void VulkanCommandEncoder::draw_indexed(const MeshHandle& handle) {
        mesh_manager->draw_indexed(this, handle);
    }

    std::shared_ptr<VulkanDevice>& VulkanCommandEncoder::get_device() {
        return device;
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
