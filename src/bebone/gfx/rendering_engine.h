#ifndef _BEBONE_GFX_RENDERING_ENGINE_H_
#define _BEBONE_GFX_RENDERING_ENGINE_H_

#include <iostream>

#include "gfx_backend.h"
#include "window/window.h"

namespace bebone::gfx {
    class RenderingEngine {
        public:
            static void preinit() {
                glfwInit();
            }

            static void init() {
                if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
                    std::cout << "Failed to initialize GLAD" << std::endl;
                    exit(1);
                }
            }

            static void setContext(const Window& window) {
                glfwMakeContextCurrent(window.get_backend()); 
            }

            static void swapBuffers(const Window& window) {
                glfwSwapBuffers(window.get_backend());
            }

            static void terminate() {
                glfwTerminate();
            }
    };
}

#endif
