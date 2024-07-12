#include "irenderer.h"

namespace bebone::renderer {
    IRenderer::IRenderer(const GfxAPI& api) : api(api) {

    }

    std::shared_ptr<IRenderGraph> IRenderer::create_render_graph(const std::string& name) {
        return std::make_shared<IRenderGraph>(name, create_render_graph_impl());
    }
}
