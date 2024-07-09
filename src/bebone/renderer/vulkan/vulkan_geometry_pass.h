#ifndef _BEBONE_RENDERER_VULKAN_GEOMETRY_PASS_H_
#define _BEBONE_RENDERER_VULKAN_GEOMETRY_PASS_H_

#include "../irenderer.h"
#include "../ipass.h"
#include "vulkan_command_encoder.h"

namespace bebone::renderer {
    class VulkanGeometryPass : public IGeometryPass {
        private:

        public:
            VulkanGeometryPass(const std::string& pass_name);

            void record(ICommandEncoder* encoder) override;
            void reset() override;
    };
}

#endif
