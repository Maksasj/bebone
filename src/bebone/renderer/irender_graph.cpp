#include "irender_graph.h"

namespace bebone::renderer {
    IRenderGraph::IRenderGraph() {

    }

    void IRenderGraph::append_pass(std::shared_ptr<IRenderPass>& render_pass) {
        render_passes.push_back(render_pass);
    }

    std::optional<std::shared_ptr<IRenderPass>> IRenderGraph::get_render_pass(const std::string& name) const {
        for(auto& pass : render_passes)
            if(pass->get_name() == name)
                return pass;

        return std::nullopt;
    }
}
