#ifndef _BEBONE_GFX_OPENGL_API_PROXY_H_
#define _BEBONE_GFX_OPENGL_API_PROXY_H_

#include "../rendering_api_proxy.h"

#include "../vulkan/vulkan_renderer.h"

namespace bebone::gfx {
    class GLApiProxy : public RenderingApiProxy {
        private:
            VulkanRenderer renderer;

        public:
            GLApiProxy(MyEngineDevice& device) : RenderingApiProxy(OPENGL), renderer(device) {
                
            }

            Renderer& get_renderer() override {
                throw std::runtime_error("Not impemented !");

                return renderer;
            }
    };
}
#endif
