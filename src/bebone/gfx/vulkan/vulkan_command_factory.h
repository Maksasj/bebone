#ifndef _BEBONE_GFX_VULKAN_VULKAN_COMMAND_FACTORY_H_
#define _BEBONE_GFX_VULKAN_VULKAN_COMMAND_FACTORY_H_

#include "../command_factory.h"

namespace bebone::gfx {
    class VulkanCommandFactory : public CommandFactory {
        public:
            Command begin_render_pass_command() const override {

            }
    };
}


#endif
