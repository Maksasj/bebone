#ifndef _BEBONE_RENDERER_IGRAPHICS_PASS_H_
#define _BEBONE_RENDERER_IGRAPHICS_PASS_H_

#include "ipass.h"

namespace bebone::renderer {
    class IGraphicsPass : public IPass {
        public:
            IGraphicsPass(const std::string& pass_name);
    };
}

#endif
