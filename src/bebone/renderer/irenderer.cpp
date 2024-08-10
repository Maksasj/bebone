#include "irenderer.h"

namespace bebone::renderer {
    IRenderer::IRenderer(const GfxAPI& api) : api(api) {

    }

    std::shared_ptr<IRenderGraph> IRenderer::create_default_render_graph(const Vec2i& viewport) {
        return std::make_shared<PBRRenderGraph>(create_render_graph_impl(), "pbr_render_graph", viewport);
    }

    std::shared_ptr<IRenderGraph> IRenderer::create_render_graph(const std::string& name) {
        return std::make_shared<IRenderGraph>(create_render_graph_impl(), name);
    }

    const GfxAPI& IRenderer::get_api() const {
        return api;
    }
}
