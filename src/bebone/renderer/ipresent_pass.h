#ifndef _BEBONE_RENDERER_IPRESENT_PASS_H_
#define _BEBONE_RENDERER_IPRESENT_PASS_H_

#include "igraphics_pass.h"

namespace bebone::renderer {
    class IPresentPass : public IGraphicsPass {
        protected:
            std::shared_ptr<IAttachment> texture_attachment;

        public:
            IPresentPass(const std::string& pass_name, const Vec2i& viewport);
    };
}

#endif
