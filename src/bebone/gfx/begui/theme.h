#ifndef _BEBONE_BEGUI_THEME_H_
#define _BEBONE_BEGUI_THEME_H_

#include <imgui.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>

#include "../window/window.h"
#include "../../core/core.h"

namespace bebone::gfx {
    void apply_default_bebone_theme();
};

#endif
