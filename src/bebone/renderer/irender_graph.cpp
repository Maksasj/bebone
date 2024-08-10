#include "irender_graph.h"

namespace bebone::renderer {
    IRenderGraph::IRenderGraph(
        const std::string& name, 
        const std::shared_ptr<IRenderGraphImpl>& impl
    ) : name(name), impl(impl) {

    }

    void IRenderGraph::assemble() {
        impl->assemble();
    }

    void IRenderGraph::record() {
        impl->record();
    }

    void IRenderGraph::submit() {
        impl->submit();
    }

    void IRenderGraph::reset() {
        impl->reset();
    }

    void IRenderGraph::resize_viewport(const Vec2i& new_size) {
        impl->resize_viewport(new_size);
    }

    void IRenderGraph::submit_geometry_task(const MeshHandle& mesh, const MaterialHandle& material, const Transform& transform) {
        std::ignore = mesh;
        std::ignore = material;
        std::ignore = transform;
    }

    void IRenderGraph::submit_ui_geometry_task(const MeshHandle& mesh, const MaterialHandle& material, const Transform& transform) {
        std::ignore = mesh;
        std::ignore = material;
        std::ignore = transform;
    }

    void IRenderGraph::add_pass(const std::shared_ptr<IPass>& render_pass) {
        impl->add_pass(render_pass);
    }

    std::optional<std::shared_ptr<IPass>> IRenderGraph::get_render_pass(const std::string& name) const {
        return impl->get_render_pass(name);
    }

    std::vector<std::shared_ptr<IPass>>& IRenderGraph::get_render_passes() {
        return impl->get_render_passes();
    }

    void IRenderGraph::add_attachment(const std::shared_ptr<IAttachment>& render_attachment) {
        impl->add_attachment(render_attachment);
    }

    std::optional<std::shared_ptr<IAttachment>> IRenderGraph::get_render_attachment(const std::string& name) const {
        return impl->get_render_attachment(name);
    }

    std::vector<std::shared_ptr<IAttachment>>& IRenderGraph::get_render_attachments() {
        return impl->get_render_attachments();
    }

    void IRenderGraph::add_target(const std::shared_ptr<IRenderTarget>& render_target) {
        impl->add_target(render_target);
    }

    std::optional<std::shared_ptr<IRenderTarget>> IRenderGraph::get_render_target(const std::string& name) const {
        return impl->get_render_target(name);
    }

    std::vector<std::shared_ptr<IRenderTarget>>& IRenderGraph::get_render_targets() {
        return impl->get_render_targets();
    }

    std::shared_ptr<IPassAssembler> IRenderGraph::create_pass_assembler() const {
        return impl->create_pass_assembler();
    }

    std::shared_ptr<IPassImplFactory> IRenderGraph::create_pass_factory() const {
        return impl->create_pass_factory();
    }

    std::shared_ptr<IAttachmentFactory> IRenderGraph::create_attachment_factory() const {
        return impl->create_attachment_factory();
    }
}
