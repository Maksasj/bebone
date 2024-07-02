#ifndef _BEBONE_RENDERER_IBINDABLE_H_
#define _BEBONE_RENDERER_IBINDABLE_H_

#include "renderer_backend.h"

namespace bebone::renderer {
    using namespace bebone::core;

    // IBindable is a some sort of object that can be binded* to render pass ?
    class IBindable {
        private:
        public:
            // Probably need to pass information about render pass | Render graph
            virtual void bind() = 0;
    };
}

#endif
