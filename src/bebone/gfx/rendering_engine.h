#ifndef _BEBONE_GFX_RENDERING_ENGINE_H_
#define _BEBONE_GFX_RENDERING_ENGINE_H_

#include "gfx_backend.h"
#include <iostream>

namespace bebone::gfx {
    class RenderingEngine {
        public:
            static void init() {
                if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
                    std::cout << "Failed to initialize GLAD" << std::endl;
                    exit(1);
                }
            }
    };
}

#endif
