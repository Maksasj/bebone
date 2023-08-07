#ifndef _BEBONE_GFX_COMMAND_BUFFER_H_
#define _BEBONE_GFX_COMMAND_BUFFER_H_

#include "../core/arena_allocator.h"

#include "model.h"
#include "swap_chain.h"
#include "pipeline.h"

#include "rendering_apis.h"

#include "gfx_backend.h"

namespace bebone::gfx {
    class CommandBuffer {
        private:

        public:
            virtual ~CommandBuffer() {}

            virtual void begin_record() = 0;
            virtual void end_record() = 0;

            virtual void begin_render_pass(MyEngineSwapChain& swapChain, int frameBuffer) = 0;
            virtual void end_render_pass() = 0;

            virtual void bind_pipeline(Pipeline& pipeline) = 0;
            virtual void bind_buffer(Model& model) = 0;
            virtual void draw(Model& model) = 0;

            virtual void submit() = 0;
            virtual void preprocess() = 0;

            virtual RenderingApi get_api() = 0;
    };
}

#endif
