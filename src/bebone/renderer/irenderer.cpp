#include "irenderer.h"

namespace bebone::renderer {
    IRenderer::IRenderer(const GfxAPI& api) : api(api) {

    }

    std::shared_ptr<IRenderGraph> IRenderer::create_default_render_graph(const Vec2i& viewport) {
        return std::make_shared<PBRRenderGraph>("pbr_render_graph", viewport, create_render_graph_impl());;
    }

    std::shared_ptr<IRenderGraph> IRenderer::create_render_graph(const std::string& name) {
        return std::make_shared<IRenderGraph>(name, create_render_graph_impl());
    }

    const GfxAPI& IRenderer::get_api() const {
        return api;
    }
}
