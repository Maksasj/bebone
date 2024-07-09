#include "igeometry_pass.h"

namespace bebone::renderer {
    IGeometryPass::IGeometryPass(const std::string& pass_name) : IPass(pass_name) {

    }

    void IGeometryPass::queue_task(const RenderTask& task) {
        render_tasks.push(task);
    }
    std::queue<RenderTask>& IGeometryPass::get_tasks() {
        return render_tasks;
    }
}
