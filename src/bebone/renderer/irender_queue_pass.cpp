#include "irender_queue_pass.h"

namespace bebone::renderer {
    IRenderQueuePass::IRenderQueuePass(
        const std::string& pass_name,
        const Vec2i& viewport
    ) : IGraphicsPass(pass_name, viewport) {

    }

    void IRenderQueuePass::submit_task(const RenderTask& task) {
        render_tasks.push(task);
    }

    std::queue<RenderTask>& IRenderQueuePass::get_tasks() {
        return render_tasks;
    }
}
