#ifndef _BEBONE_RENDERER_IRENDER_QUEUE_PASS_H_
#define _BEBONE_RENDERER_IRENDER_QUEUE_PASS_H_

#include "igraphics_pass.h"
#include "itexture_resource.h"
#include "idepth_resource.h"
#include "imesh.h"
#include "transform.h"

namespace bebone::renderer {
    using namespace bebone::core;

    class IRenderQueuePass : public IGraphicsPass {
        public:
            IRenderQueuePass(const std::string& pass_name, const Vec2i& viewport);

            virtual void submit_task(const std::shared_ptr<IMesh>& mesh, const Transform& transform) = 0;
    };
}

#endif
