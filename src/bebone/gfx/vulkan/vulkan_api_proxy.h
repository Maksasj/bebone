#ifndef _BEBONE_GFX_VULKAN_API_PROXY_H_
#define _BEBONE_GFX_VULKAN_API_PROXY_H_

#include "../command_factory.h"
#include "../rendering_api_proxy.h"

#include "vulkan_command_factory.h"

namespace bebone::gfx {
    class VulkanApiProxy : public RenderingApiProxy {
        private:
            VulkanRenderer renderer;
            VulkanCommandFactory commandFactory;

        public:
            VulkanApiProxy() : RenderingApiProxy(VULKAN) {
                
            }

            Renderer& get_renderer() override {
                return renderer;
            }

            CommandFactory& get_command_factory() override {
                return commandFactory;
            }
    };
}
#endif
