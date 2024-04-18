#ifndef _BEBONE_BEGUI_BEGUI_H_
#define _BEBONE_BEGUI_BEGUI_H_

#include <imgui.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>

#include "../window/window.h"
#include "../../core/core.h"

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

        private:
            /*!
            * Traces profile tree and renders as ImGUI ui
            * @param parent - Pointer to profile
            */
            static void profiler_trace_profiles(Profile* parent);

        public:
            // Function that renders ImGUI profiler window
            static void show_profiler();
    };
};

#endif
