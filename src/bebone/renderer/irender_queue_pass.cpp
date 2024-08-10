#include "irender_queue_pass.h"

namespace bebone::renderer {
    IRenderQueuePass::IRenderQueuePass(
        const std::shared_ptr<IPassImpl>& impl,
        const std::string& pass_name,
        const Vec2i& viewport
    ) : IGraphicsPass(impl, pass_name, viewport) {

    }

    void IRenderQueuePass::reset() {
        queued_jobs.clear();
    }

    void IRenderQueuePass::submit_task(const RenderQueueTask& task)  {
        queued_jobs.push_back(task);
    }
}
