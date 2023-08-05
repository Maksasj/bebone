#ifndef _BEBONE_GFX_RENDERING_API_PROXY_H_
#define _BEBONE_GFX_RENDERING_API_PROXY_H_

#include "rendering_apis.h"

#include "renderer.h"
#include "command_factory.h"

namespace bebone::gfx {
    class RenderingApiProxy {
        private:
            const RenderingApis _api;
        public:
            RenderingApiProxy(const RenderingApis& api) : _api(api) {

            }

            virtual Renderer& get_renderer() = 0;
            virtual CommandFactory& get_command_factory() = 0;

            RenderingApis get_api() const {
                return _api;
            }
    };
}

#endif
