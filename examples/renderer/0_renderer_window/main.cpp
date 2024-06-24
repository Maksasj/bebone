#include "bebone/bebone.h"

using namespace bebone::renderer;
using namespace bebone::gfx;

int main() {
    GLFWContext::init(); // this should be moved somewhere else

    auto window = WindowFactory::create_window("0. Renderer window example", 800, 600, GfxAPI::OPENGL);
    auto renderer = window->create_renderer();

    auto sprite = renderer->load_sprite("image.png");

    while(!window->closing()) {
        renderer->render(sprite, { .pos = Vec3f::zero });
        renderer->present();
    }

    GLFWContext::terminate();// this should be moved somewhere else

    return 0;
}
