#ifndef BEXEL_BEXEL_H
#define BEXEL_BEXEL_H

#include "world/world.h"
#include "camera.h"

namespace bexel {
    static const u64 game_width = 800;
    static const u64 game_height = 600;

    class Bexel {
    private:
        shared_ptr<Window> window;

        unique_ptr<GLShaderProgram> shader;
        unique_ptr<GLTexture2D> texture;

        unique_ptr<Camera> camera;
        unique_ptr<World> world;

    public:
        Bexel();

        void init();

        void load();

        void run();

        void unload();
    };
}

#endif
