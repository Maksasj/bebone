#ifndef _BEBONE_GFX_VULKAN_API_PROXY_H_
#define _BEBONE_GFX_VULKAN_API_PROXY_H_

#include "vulkan_renderer_impl.h"
#include "../rendering_api_proxy.h"

namespace bebone::gfx {
    class VulkanApiProxy : public RenderingApiProxy {
        private:
            VulkanRendererImpl renderer;

        public:
            VulkanApiProxy(Window& window) : RenderingApiProxy(VULKAN), renderer(window) {
                
            }

            RendererImpl& get_renderer() override {
                return renderer;
            }
    };
}
#endif
