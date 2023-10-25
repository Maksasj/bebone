#ifndef _OPENGL_CONTEXT_H_
#define _OPENGL_CONTEXT_H_

#include "../gfx_backend.h"

namespace bebone::gfx::opengl {
    using namespace bebone::core;

    struct GLContext {
        static void inline set_viewport(const i32& x, const i32& y, const i32& width, const i32& height) {
            glViewport(x, y, width, height);
        }

        static void inline clear(const GLbitfield& mask) {
            glClear(mask);
        }

        static void inline clear_color(const f32& r, const f32& g, const f32& b, const f32& a) {
            glClearColor(r, g, b, a);
        }

        static void inline clear_color(const Vec4f& color) {
            clear_color(color.x, color.y, color.z, color.w);
        }

        static void inline clear_color(const Vec3f& color) {
            clear_color(color.x, color.y, color.z, 1.0f);
        }

        static void inline draw_arrays(const GLenum& mode, const i32& first, const i32& count) {
            glDrawArrays(mode, first, count);
        }

        static void inline draw_elements(const GLenum& mode, const i32& size, const GLenum& type, const void* indices) {
            glDrawElements(mode, size, type, indices);
        }
    };
}

#endif
