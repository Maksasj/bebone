#ifndef _BEBONE_RENDERER_RENDERER_FACTORY_H_
#define _BEBONE_RENDERER_RENDERER_FACTORY_H_

#include "renderer_backend.h"
#include "irenderer.h"

namespace bebone::renderer {
    class RendererFactory {
        public:
            static std::shared_ptr<IRenderer> create_renderer(std::shared_ptr<gfx::Window>& window);
    };
}

#endif
