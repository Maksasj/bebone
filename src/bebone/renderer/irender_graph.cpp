#include "irender_graph.h"

namespace bebone::renderer {
    IRenderGraph::IRenderGraph(const std::string& name) : name(name) {

    }

    void IRenderGraph::add_pass(const std::shared_ptr<IPass>& render_pass) {
        render_passes.push_back(render_pass);
    }

    std::optional<std::shared_ptr<IPass>> IRenderGraph::get_render_pass(const std::string& pass_name) const {
        for(auto& pass : render_passes)
            if(pass->get_name() == pass_name)
                return pass;

        return std::nullopt;
    }

    std::vector<std::shared_ptr<IPass>>& IRenderGraph::get_render_passes() {
        return render_passes;
    }

    void IRenderGraph::add_resource(const std::shared_ptr<IResource>& render_resource) {
        render_resources.push_back(render_resource);
    }

    std::optional<std::shared_ptr<IResource>> IRenderGraph::get_render_resource(const std::string& resource_name) const {
        for(auto& resource : render_resources)
            if(resource->get_name() == resource_name)
                return resource;

        return std::nullopt;
    }

    std::vector<std::shared_ptr<IResource>>& IRenderGraph::get_render_resources() {
        return render_resources;
    }
}
