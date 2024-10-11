#ifndef _BEBONE_RENDERER_IDEFERRED_G_PASS_H_
#define _BEBONE_RENDERER_IDEFERRED_G_PASS_H_

#include <string>
#include "irender_queue_pass.h"

namespace bebone::renderer {
    using namespace bebone::core;
    using namespace bebone::gfx;

    class IDeferredGPass : public IRenderQueuePass {
        private:
            std::shared_ptr<IUniformBuffer> camera_ubo;

        protected:
            std::shared_ptr<IRenderTarget> render_target;

        public:
            IDeferredGPass(const std::shared_ptr<IPassImpl>& impl, const std::string& pass_name, const Vec2i& viewport);

            void assemble(std::shared_ptr<IPassAssembler>& assember) override;
            void record(ICommandEncoder* encoder) override;
    };
}

#endif
