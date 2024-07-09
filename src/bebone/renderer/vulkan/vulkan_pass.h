#ifndef _BEBONE_RENDERER_VULKAN_PASS_H_
#define _BEBONE_RENDERER_VULKAN_PASS_H_

#include "../irenderer.h"
#include "../ipass.h"

namespace bebone::renderer {
    using namespace bebone::gfx;

    class VulkanPresentPass : public IPresentPass {
        private:

        public:
            VulkanPresentPass(const std::string& pass_name);

            void execute() override;
            void reset() override;
    };

    class VulkanGeometryPass : public IGeometryPass {
        private:

        public:
            VulkanGeometryPass(const std::string& pass_name);

            void execute() override;
            void reset() override;
    };
}

#endif
