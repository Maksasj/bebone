#ifndef _BEBONE_RENDERER_IDEFERRED_G_PASS_H_
#define _BEBONE_RENDERER_IDEFERRED_G_PASS_H_

#include <string>
#include "irender_queue_pass.h"

namespace bebone::renderer {
    using namespace bebone::core;

    class IDeferredGPass : public IRenderQueuePass {
        protected:
            std::shared_ptr<IAttachment> position_attachment;
            std::shared_ptr<IAttachment> normals_attachment;
            std::shared_ptr<IAttachment> albedo_attachment;
            std::shared_ptr<IAttachment> specular_attachment;

            std::shared_ptr<IAttachment> depth_attachment;

        public:
            IDeferredGPass(const std::shared_ptr<IPassImpl>& impl, const std::string& pass_name, const Vec2i& viewport);
    };
}

#endif
