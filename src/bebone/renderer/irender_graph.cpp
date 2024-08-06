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

    std::optional<std::shared_ptr<IPass>> IRenderGraph::get_render_pass(const std::string& pass_name) const {
        return impl->get_render_pass(pass_name);
    }

    std::vector<std::shared_ptr<IPass>>& IRenderGraph::get_render_passes() {
        return impl->get_render_passes();
    }

    void IRenderGraph::add_attachment(const std::shared_ptr<IAttachment>& render_attachment) {
        impl->add_attachment(render_attachment);
    }

    std::optional<std::shared_ptr<IAttachment>> IRenderGraph::get_render_attachment(const std::string& attachment_name) const {
        return impl->get_render_attachment(attachment_name);
    }

    std::vector<std::shared_ptr<IAttachment>>& IRenderGraph::get_render_attachments() {
        return impl->get_render_attachments();
    }

    std::shared_ptr<IPassImplFactory> IRenderGraph::create_pass_factory() const {
        return impl->create_pass_factory();
    }

    std::shared_ptr<IAttachmentFactory> IRenderGraph::create_attachment_factory() const {
        return impl->create_attachment_factory();
    }
}
