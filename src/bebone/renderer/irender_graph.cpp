#include "irender_graph.h"

namespace bebone::renderer {
    IRenderGraph::IRenderGraph(
        const std::string& name, 
        std::unique_ptr<IRenderGraphImpl> impl
    ) : name(name), impl(std::move(impl)) {

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

    void IRenderGraph::add_pass(const std::shared_ptr<IPass>& render_pass) {
        impl->add_pass(render_pass);
    }

    std::optional<std::shared_ptr<IPass>> IRenderGraph::get_render_pass(const std::string& pass_name) const {
        return impl->get_render_pass(pass_name);
    }

    std::vector<std::shared_ptr<IPass>>& IRenderGraph::get_render_passes() {
        return impl->get_render_passes();
    }

    void IRenderGraph::add_resource(const std::shared_ptr<IResource>& render_resource) {
        impl->add_resource(render_resource);
    }

    std::optional<std::shared_ptr<IResource>> IRenderGraph::get_render_resource(const std::string& resource_name) const {
        return impl->get_render_resource(resource_name);
    }

    std::vector<std::shared_ptr<IResource>>& IRenderGraph::get_render_resources() {
        return impl->get_render_resources();
    }

    std::shared_ptr<IPassFactory> IRenderGraph::create_pass_factory() const {
        return impl->create_pass_factory();
    }

    std::shared_ptr<IResourceFactory> IRenderGraph::create_resource_factory() const {
        return impl->create_resource_factory();
    }
}
