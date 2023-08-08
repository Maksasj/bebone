#ifndef _BEBONE_GFX_RENDERING_API_PROXY_H_
#define _BEBONE_GFX_RENDERING_API_PROXY_H_

#include "rendering_apis.h"
#include "renderer_impl.h"

namespace bebone::gfx {
    class RenderingApiProxy {
        private:
            const RenderingApi _api;
        public:
            RenderingApiProxy(const RenderingApi& api) : _api(api) {

            }

            virtual ~RenderingApiProxy() {}

            virtual RendererImpl& get_renderer() = 0;

            RenderingApi get_api() const {
                return _api;
            }
    };
}

#endif
