#ifndef _BEBONE_GFX_RENDERIN_API_PROXY_PROVIDER_H_
#define _BEBONE_GFX_RENDERIN_API_PROXY_PROVIDER_H_

#include <exception>
#include <memory>

#include "rendering_apis.h"
#include "rendering_api_proxy.h"

#include "vulkan/vulkan_api_proxy.h"
#include "opengl/gl_api_proxy.h"

namespace bebone::gfx {
    class RenderingApiProxyProvider {
        public:
            static std::unique_ptr<RenderingApiProxy> get_proxy(const RenderingApi& api, MyEngineDevice& device) {
                switch (api) {
                    case RenderingApi::OPENGL: return std::make_unique<GLApiProxy>(device);
                    case RenderingApi::VULKAN: return std::make_unique<VulkanApiProxy>(device);
                    default: throw std::runtime_error("Failed to get rendering api proxy, rendering api not implemented");
                }
                
                throw std::runtime_error("Failed to get rendering api proxy, rendering api not implemented");
                // return std::unique_ptr<RenderingApiProxy>(nullptr);
            }   
    };
}
#endif
