#include "vulkan_command_encoder.h"
#include "../iprogram.h"
#include "vulkan_program.h"

namespace bebone::renderer {
    using namespace bebone::gfx;

    VulkanCommandEncoder::VulkanCommandEncoder(
        const std::shared_ptr<VulkanDevice>& device,
        const std::shared_ptr<VulkanSwapChain>& swap_chain,
        const std::shared_ptr<VulkanCommandBuffer>& command_buffer,
        const size_t& frame,
        const std::shared_ptr<IMeshManager>& mesh_manager
    ) : ICommandEncoder(mesh_manager), device(device), swap_chain(swap_chain), command_buffer(command_buffer), frame(frame) {

    }

    void VulkanCommandEncoder::begin_render_pass(const std::shared_ptr<IRenderTarget>& render_target, const std::shared_ptr<IPassImpl>& pass) {
        auto vulkan_pass = static_pointer_cast<VulkanPassImpl>(pass)->get_vulkan_pass();
        auto vulkan_render_target_impl = static_pointer_cast<renderer::VulkanRenderTargetImpl>(render_target->get_impl());
        auto framebuffers = vulkan_render_target_impl->get_framebuffers();

        command_buffer->begin_render_pass(framebuffers[frame], vulkan_pass);
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

    void VulkanCommandEncoder::bind_draw_data(const std::shared_ptr<IProgram>& program, const Transform& transform, const std::shared_ptr<IUniformBuffer>& camera, const MaterialHandle& material) {
        auto handles = DeferredGPassDrawData {
            .transform = calculate_transform_matrix(transform),
            .camera_handle = camera->get_handle(),
            .material_handle = material
        };

        auto pipeline_layout = static_pointer_cast<VulkanProgram>(program)->get_pipeline_layout();
        command_buffer->push_constant(pipeline_layout, sizeof(DeferredGPassDrawData), 0, &handles);
    }

    void VulkanCommandEncoder::bind_draw_data(const std::shared_ptr<IProgram>& program, const std::shared_ptr<IAttachment>& attachment) {
        const auto texture = static_pointer_cast<VulkanAttachmentImpl>(attachment->get_impl());
        auto handles = u32(texture->get_handles()[frame]);

        auto pipeline_layout = static_pointer_cast<VulkanProgram>(program)->get_pipeline_layout();
        command_buffer->push_constant(pipeline_layout, sizeof(u32), 0, &handles);
    }

    void VulkanCommandEncoder::draw_indexed(const MeshHandle& handle) {
        get_mesh_manager()->draw_indexed(this, handle);
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
