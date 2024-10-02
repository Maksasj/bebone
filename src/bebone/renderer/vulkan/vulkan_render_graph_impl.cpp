#include "vulkan_render_graph_impl.h"

namespace bebone::renderer {
    VulkanRenderGraphImpl::VulkanRenderGraphImpl(
        const std::shared_ptr<VulkanDevice>& device,
        const std::shared_ptr<VulkanSwapChain>& swap_chain,
        const std::shared_ptr<VulkanProgramManager>& program_manager,
        const std::shared_ptr<VulkanTextureManager>& texture_manager,
        const std::shared_ptr<VulkanMeshManager>& mesh_manager,
        const std::shared_ptr<VulkanMaterialManager>& material_manager
    ) : IRenderGraphImpl(), device(device), swap_chain(swap_chain), program_manager(program_manager), texture_manager(texture_manager), mesh_manager(mesh_manager), material_manager(material_manager) {
        for(size_t i = 0; i < 3; ++i) // Todo, fif
            encoders.emplace_back(device, swap_chain, device->create_command_buffer(), i, mesh_manager);
    }

    void VulkanRenderGraphImpl::assemble() {
        auto assembler = create_pass_assembler();

        for(auto& pass : get_render_passes())
            pass->assemble(assembler);
    }

    void VulkanRenderGraphImpl::record() {
        if(!swap_chain->acquire_next_image(device, &frame).is_ok()) {
            LOG_TRACE("Window is resized");
            return;
        }

        auto& encoder = encoders[frame];
        auto cmd = encoder.get_command_buffer();

        cmd->begin_record();

        // Bind bindless descriptor set
        cmd->bind_descriptor_set(program_manager->get_pipeline_layout(), program_manager->get_descriptor_set());

        for(auto& pass : get_render_passes())
            pass->record(&encoder);

        cmd->end_record();
    }

    void VulkanRenderGraphImpl::submit() {
        auto cmd = encoders[frame].get_command_buffer();

        if(!swap_chain->submit_present_command_buffers(device, cmd, &frame).is_ok()) {
            LOG_TRACE("Window is resized");
            return;
        }
    }

    void VulkanRenderGraphImpl::reset() {
        for(auto& pass : get_render_passes())
            pass->reset();
    }

    void VulkanRenderGraphImpl::resize_viewport(const Vec2i& new_size) {
        for(auto& pass : get_render_passes())
            pass->resize_viewport(new_size);
    }

    std::shared_ptr<IPassAssembler> VulkanRenderGraphImpl::create_pass_assembler() const {
        return std::make_shared<VulkanPassAssembler>(
            device,
            swap_chain,
            program_manager,
            texture_manager,
            mesh_manager,
            material_manager);
    }

    std::shared_ptr<IPassImplFactory> VulkanRenderGraphImpl::create_pass_factory() const {
        return std::make_shared<VulkanPassImplFactory>(device, swap_chain);
    }

    std::shared_ptr<IAttachmentFactory> VulkanRenderGraphImpl::create_attachment_factory() const {
        return std::make_shared<VulkanAttachmentFactory>(texture_manager);
    }
}
