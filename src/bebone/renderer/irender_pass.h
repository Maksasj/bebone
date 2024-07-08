#ifndef _BEBONE_RENDERER_IRENDER_PASS_H_
#define _BEBONE_RENDERER_IRENDER_PASS_H_

#include <string>

#include "renderer_backend.h"

namespace bebone::renderer {
    class IRenderPass {
        private:
            std::string name;

        public:
            const std::string& get_name() const;
    };
}

#endif
