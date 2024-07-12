#ifndef _BEBONE_RENDERER_IPRESENT_PASS_H_
#define _BEBONE_RENDERER_IPRESENT_PASS_H_

#include "igraphics_pass.h"

namespace bebone::renderer {
    class IPresentPass : public IGraphicsPass {
        private:

        protected:
            std::shared_ptr<IResource> texture_resource;

        public:
            IPresentPass(const std::string& pass_name);
    };
}

#endif
