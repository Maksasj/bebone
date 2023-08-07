#ifndef _BEBONE_GFX_OPENGL_API_PROXY_H_
#define _BEBONE_GFX_OPENGL_API_PROXY_H_

#include "../rendering_api_proxy.h"

#include "../vulkan/vulkan_renderer.h"

namespace bebone::gfx {
    class GLApiProxy : public RenderingApiProxy {
        private:
            VulkanRenderer renderer;

        public:
            GLApiProxy(Window& window) : RenderingApiProxy(OPENGL), renderer(window) {
                
            }

            Renderer& get_renderer() override {
                throw std::runtime_error("Not impemented !");

                return renderer;
            }
    };
}
#endif
