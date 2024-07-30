#include "vulkan_render_graph_impl.h"

namespace bebone::renderer {
    VulkanRenderGraphImpl::VulkanRenderGraphImpl(
        const std::shared_ptr<VulkanDevice>& device,
        const std::shared_ptr<VulkanSwapChain>& swap_chain,
        const std::shared_ptr<VulkanProgramManager>& program_manager,
        const std::shared_ptr<VulkanTextureManager>& texture_manager,
        const std::shared_ptr<VulkanMeshManager>& mesh_manager
    ) : IRenderGraphImpl(), device(device), swap_chain(swap_chain), program_manager(program_manager), texture_manager(texture_manager), mesh_manager(mesh_manager) {
        command_buffers = device->create_command_buffers(3);
    }

    void VulkanRenderGraphImpl::assemble() {
        VulkanPassAssembler assembler(
            device,
            swap_chain,
            program_manager,
            texture_manager,
            mesh_manager);

        for(auto& pass : get_render_passes())
            pass->assemble(&assembler);
    }

    void VulkanRenderGraphImpl::record() {
        if(!swap_chain->acquire_next_image(device, &frame).is_ok())
            return;

        auto& cmd = command_buffers[frame];
        VulkanCommandEncoder encoder(device, swap_chain, cmd, frame); // Todo rewrite vulkan command encoder

        cmd->begin_record();

        cmd->bind_descriptor_set(program_manager->get_pipeline_layout(), program_manager->get_descriptor_set());

        for(auto& pass : get_render_passes())
            pass->record(&encoder);

        cmd->end_record();
    }

    void VulkanRenderGraphImpl::submit() {
        if(!swap_chain->submit_present_command_buffers(device, command_buffers[frame], &frame).is_ok()) // Todo check if window is resized
            return;
    }

    void VulkanRenderGraphImpl::reset() {
        for(auto& pass : get_render_passes())
            pass->reset();
    }

    void VulkanRenderGraphImpl::resize_viewport(const Vec2i& new_size) {
        for(auto& pass : get_render_passes())
            pass->resize_viewport(new_size);
    }

    std::shared_ptr<IPassFactory> VulkanRenderGraphImpl::create_pass_factory() const {
        return std::make_shared<VulkanPassFactory>(device, swap_chain);
    }

    std::shared_ptr<IResourceFactory> VulkanRenderGraphImpl::create_resource_factory() const {
        return std::make_shared<VulkanResourceFactory>(device, texture_manager);
    }
}
