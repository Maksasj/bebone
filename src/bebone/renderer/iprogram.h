#ifndef _BEBONE_RENDERER_IPROGRAM_H_
#define _BEBONE_RENDERER_IPROGRAM_H_

#include "renderer_backend.h"

namespace bebone::renderer {
    class ICommandEncoder;

    using namespace bebone::core;

    class IProgram : private core::NonCopyable {
        public:
            virtual ~IProgram() = default;

            virtual void bind(ICommandEncoder* encoder) = 0;
    };
}

#endif
