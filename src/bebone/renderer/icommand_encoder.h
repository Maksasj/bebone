#ifndef _BEBONE_RENDERER_ICOMMAND_ENCODER_H_
#define _BEBONE_RENDERER_ICOMMAND_ENCODER_H_

#include "renderer_backend.h"

#include "iprogram.h"

namespace bebone::renderer {
    using namespace bebone::core;

    class ICommandEncoder {
        private:

        public:
            virtual void set_viewport(const Vec2i& viewport) = 0;
            virtual void bind_program(const std::shared_ptr<IProgram>& program) = 0;
    };
}

#endif
