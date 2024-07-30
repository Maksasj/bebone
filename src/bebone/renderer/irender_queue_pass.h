#ifndef _BEBONE_RENDERER_IRENDER_QUEUE_PASS_H_
#define _BEBONE_RENDERER_IRENDER_QUEUE_PASS_H_

#include "igraphics_pass.h"
#include "ihdr_texture_resource.h"
#include "idepth_resource.h"
#include "transform.h"

#include "mesh/imesh.h"
#include "imaterial_impl.h"

namespace bebone::renderer {
    using namespace bebone::core;

    struct RenderQueueTask {
        MeshHandle mesh;
        MaterialHandle material;
    };

    class IRenderQueuePass : public IGraphicsPass {
        public:
            IRenderQueuePass(const std::string& pass_name, const Vec2i& viewport);

            virtual void submit_task(const RenderQueueTask& task, const Transform& transform) = 0;
    };
}

#endif
