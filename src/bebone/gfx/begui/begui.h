#ifndef _BEBONE_BEGUI_BEGUI_H_
#define _BEBONE_BEGUI_BEGUI_H_

#include <imgui.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>

#include "../window/window.h"
#include "../../core/core.h"

#include "theme.h"

namespace bebone::gfx {
    class BeGUI {
        public:
            static void init(const std::shared_ptr<Window>& window);

            static void begin();
            static void end();

        private:
            static void profiler_trace_profiles(Profile* profile);

        public:
            static void show_profiler();
    };
};

#endif
