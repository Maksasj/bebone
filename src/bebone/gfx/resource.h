#ifndef _BEBONE_GFX_RESOURCE_H_
#define _BEBONE_GFX_RESOURCE_H_

#include "resource_handler.h"

namespace bebone::gfx {
    class Resource {
        private:

        public:
            virtual ResourceHandler get_handler(const size_t& index) = 0;
    };
}

#endif
