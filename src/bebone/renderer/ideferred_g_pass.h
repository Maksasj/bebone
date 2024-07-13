#ifndef _BEBONE_RENDERER_IDEFERRED_G_PASS_H_
#define _BEBONE_RENDERER_IDEFERRED_G_PASS_H_

#include <string>
#include "irender_queue_pass.h"
#include "ihdr_texture_resource.h"
#include "idepth_resource.h"

namespace bebone::renderer {
    using namespace bebone::core;

    class IDeferredGPass : public IRenderQueuePass {
        protected:
            std::shared_ptr<IResource> position_resource;
            std::shared_ptr<IResource> normals_resource;
            std::shared_ptr<IResource> albedo_resource;
            std::shared_ptr<IResource> specular_resource;

            std::shared_ptr<IResource> depth_resource;

        public:
            IDeferredGPass(const std::string& pass_name, const Vec2i& viewport);
    };
}

#endif
