#include "bebone/bebone.h"

using namespace bebone::renderer;
using namespace bebone::gfx;

int main() {
    GLFWContext::init(); // this should be moved somewhere else

    auto window = WindowFactory::create_window("1. Renderer hello triangle", 800, 600, GfxAPI::OpenGL);
    auto renderer = window->create_renderer();

    auto sprite = renderer->load_sprite("image.png");

    while(!window->closing()) {
        renderer->render(sprite, { .pos = Vec3f::zero });
        renderer->present();
    }

    GLFWContext::terminate();// this should be moved somewhere else

    return 0;
}
