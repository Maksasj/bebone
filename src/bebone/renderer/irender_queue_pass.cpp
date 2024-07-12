#include "irender_queue_pass.h"

namespace bebone::renderer {
    IRenderQueuePass::IRenderQueuePass(const std::string& pass_name) : IPass(pass_name) {
        register_output("texture", texture_resource);
        register_output("depth", depth_resource);
    }

    void IRenderQueuePass::queue_task(const RenderTask& task) {
        render_tasks.push(task);
    }

    std::queue<RenderTask>& IRenderQueuePass::get_tasks() {
        return render_tasks;
    }
}
