#ifndef _BEBONE_RENDERER_IRENDER_QUEUE_PASS_H_
#define _BEBONE_RENDERER_IRENDER_QUEUE_PASS_H_

#include "igraphics_pass.h"
#include "transform.h"

#include "mesh/imesh_impl.h"
#include "imaterial_impl.h"

namespace bebone::renderer {
    using namespace bebone::core;

    struct RenderQueueTask {
        MeshHandle mesh;
        MaterialHandle material;
        Transform transform;
    };

    class IRenderQueuePass : public IGraphicsPass {
        protected:
            std::vector<RenderQueueTask> queued_jobs;

        public:
            IRenderQueuePass(const std::shared_ptr<IPassImpl>& impl, const std::string& pass_name, const Vec2i& viewport);

            void reset() override;
            virtual void submit_task(const RenderQueueTask& task);
    };
}

#endif
