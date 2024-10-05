#ifndef _BEBONE_RENDERER_RENDERER_FACTORY_H_
#define _BEBONE_RENDERER_RENDERER_FACTORY_H_

#include "renderer_backend.h"
#include "irenderer.h"

namespace bebone::renderer {
    class RendererFactory {
        public:
            static std::shared_ptr<IRenderer> create_renderer(std::shared_ptr<gfx::Window>& window);
    };

    std::pair<std::shared_ptr<Window>, std::shared_ptr<IRenderer>> create_window_renderer(const std::string& title, const int& width, const int& height, const GfxAPI& gfx_api, const WindowProperties& properties);
}

#endif
