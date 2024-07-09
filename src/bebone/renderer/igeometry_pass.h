#ifndef _BEBONE_RENDERER_IGEOMETRY_PASS_H_
#define _BEBONE_RENDERER_IGEOMETRY_PASS_H_

#include "ipass.h"

namespace bebone::renderer {
    class IGeometryPass : public IPass {
        private:

        public:
            IGeometryPass(const std::string& pass_name) : IPass(pass_name) {

            }
    };
}

#endif
