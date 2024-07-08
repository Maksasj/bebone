#ifndef _BEBONE_RENDERER_IRENDER_PASS_H_
#define _BEBONE_RENDERER_IRENDER_PASS_H_

#include <string>

#include "renderer_backend.h"

namespace bebone::renderer {
    class IRenderPass {
        private:
            std::string name;

        public:
            IRenderPass(const std::string& name);

            virtual void execute() = 0;
            virtual void reset() = 0;

            const std::string& get_name() const;
    };

    class IBindingPass : public IRenderPass {
        private:

        public:
    };

    class IRenderQueuePass : public IBindingPass {
        private:

        public:

    };

    // Not sure about this
    class IFullScreenPass : public IBindingPass {
        private:

        public:
    };

    class ISwapChainPresentPass : public IRenderPass {
        private:

        public:
    };
}

#endif
