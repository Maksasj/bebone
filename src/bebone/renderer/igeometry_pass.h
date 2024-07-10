#ifndef _BEBONE_RENDERER_IGEOMETRY_PASS_H_
#define _BEBONE_RENDERER_IGEOMETRY_PASS_H_

#include "ipass.h"

#include "itexture_resource.h"
#include "idepth_resource.h"

namespace bebone::renderer {
    using RenderTask = std::function<void(ICommandEncoder*)>;

    class IGeometryPass : public IPass {
        private:
            std::queue<RenderTask> render_tasks;

        protected:
            std::shared_ptr<IResource> texture_resource;
            std::shared_ptr<IResource> depth_resource;

        public:
            IGeometryPass(const std::string& pass_name);

            void queue_task(const RenderTask& task);
            std::queue<RenderTask>& get_tasks();
    };
}

#endif
