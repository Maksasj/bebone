#ifndef _BEBONE_RENDERER_ICOMMAND_ENCODER_H_
#define _BEBONE_RENDERER_ICOMMAND_ENCODER_H_

#include "renderer_backend.h"

#include "irender_target.h"
#include "ipass_impl.h"
#include "iprogram.h"

namespace bebone::renderer {
    using namespace bebone::core;

    class ICommandEncoder {
        private:

        public:
            virtual void begin_render_pass(const std::shared_ptr<IRenderTarget>& render_target, const std::shared_ptr<IPassImpl>& pass) = 0;
            virtual void end_render_pass() = 0;

            virtual void set_viewport(const Vec2i& viewport) = 0;
            virtual void bind_program(const std::shared_ptr<IProgram>& program) = 0;
    };
}

#endif
