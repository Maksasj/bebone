#ifndef _BEBONE_RENDERER_IPROGRAM_H_
#define _BEBONE_RENDERER_IPROGRAM_H_

#include "renderer_backend.h"

namespace bebone::renderer {
    using namespace bebone::gfx;

    class IProgram {
        private:

        public:
            virtual void bind(ICommandEncoder* encoder) = 0;
    };

    class OpenGLProgram : public IProgram {
        private:
    };

    class VulkanProgram : public IProgram {
        private:
            std::optional<VulkanManagedPipelineTuple> pipeline;

        public:
            void bind(ICommandEncoder* encoder) override;
    };
}

#endif
