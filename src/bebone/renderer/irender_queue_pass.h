#ifndef _BEBONE_RENDERER_IRENDER_QUEUE_PASS_H_
#define _BEBONE_RENDERER_IRENDER_QUEUE_PASS_H_

#include "igraphics_pass.h"
#include "itexture_resource.h"
#include "idepth_resource.h"

namespace bebone::renderer {
    using namespace bebone::core;

    using RenderTask = std::function<void(ICommandEncoder*)>;

    class IRenderQueuePass : public IGraphicsPass {
        private:
            std::queue<RenderTask> render_tasks;

        public:
            IRenderQueuePass(const std::string& pass_name, const Vec2i& viewport);

            void submit_task(const RenderTask& task);
            std::queue<RenderTask>& get_tasks();
    };
}

#endif
