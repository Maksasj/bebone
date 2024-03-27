#ifndef _BEBONE_GFX_GFX_BACKEND_H_
#define _BEBONE_GFX_GFX_BACKEND_H_

#include <glad/glad.h>

#include <stb_image.h>

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

// Shader things
#include <SPIRV/GlslangToSpv.h>
#include <glslang/Public/ShaderLang.h>
#include <glslang/Public/ResourceLimits.h>

// Bebone things
#ifndef OMNI_GLAD_INTEGRATION
    #define OMNI_GLAD_INTEGRATION
#endif

#include "../core/core.h"

#endif
