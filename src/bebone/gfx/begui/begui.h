#ifndef _BEBONE_BEGUI_BEGUI_H_
#define _BEBONE_BEGUI_BEGUI_H_

#include <imgui.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>

#include "../window/window.h"
#include "theme.h"

namespace bebone::gfx {
    // Dear ImGUI abstraction class
    class BeGUI {
        public:
            /*!
            * Initializes Dear ImGUI
            * @param window - bebone window
            */
            static void init(const std::shared_ptr<Window>& window);

            // Begin ImGUI context
            static void begin();

            // Ends ImGUI context
            static void end();
    };
};

#endif
