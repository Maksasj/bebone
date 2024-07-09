#ifndef _BEBONE_RENDERER_IPRESENT_PASS_H_
#define _BEBONE_RENDERER_IPRESENT_PASS_H_

#include "ipass.h"

namespace bebone::renderer {
    class IPresentPass : public IPass {
        private:

        public:
            IPresentPass(const std::string& pass_name) : IPass(pass_name) {

            }
    };
}

#endif
