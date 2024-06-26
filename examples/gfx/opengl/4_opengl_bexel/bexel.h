#ifndef BEXEL_BEXEL_H
#define BEXEL_BEXEL_H

#include "gfx/opengl/4_opengl_bexel/world/world.h"
#include "camera.h"

namespace bexel {
    static const u64 GAME_WIDTH = 800;
    static const u64 GAME_HEIGHT = 600;

    class Bexel {
    private:
        shared_ptr<Window> m_window;

        unique_ptr<GLShaderProgram> m_shader;
        unique_ptr<GLTexture2D> m_texture;

        unique_ptr<Camera> m_camera;
        unique_ptr<World> m_world;

    public:
        Bexel();

        void init();

        void load();

        void run();

        void unload();
    };
}

#endif
