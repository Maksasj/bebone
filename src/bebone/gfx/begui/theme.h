#ifndef _BEBONE_BEGUI_THEME_H_
#define _BEBONE_BEGUI_THEME_H_

#include <imgui.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>

namespace bebone::gfx {
    // Applies Dear ImGUI bebone default theme
    void apply_default_bebone_imgui_theme();
};

#endif
