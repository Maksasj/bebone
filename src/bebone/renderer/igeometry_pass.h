#ifndef _BEBONE_RENDERER_IGEOMETRY_PASS_H_
#define _BEBONE_RENDERER_IGEOMETRY_PASS_H_

#include "ipass.h"

namespace bebone::renderer {
    using RenderTask = std::function<void(ICommandEncoder*)>;

    class IGeometryPass : public IPass {
        private:
            std::queue<RenderTask> render_tasks;

        public:
            IGeometryPass(const std::string& pass_name);

            void queue_task(const RenderTask& task);
            std::queue<RenderTask>& get_tasks();
    };
}

#endif
