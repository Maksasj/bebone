#include "bebone/bebone.h"

using namespace bebone::renderer;
using namespace bebone::gfx;

int main() {
    GLFWContext::init(); // this should be moved somewhere else

    auto window = WindowFactory::create_window("3. Renderer mesh", 800, 600, Vulkan, { .enable_resize = true });
    auto renderer = RendererFactory::create_renderer(window);

    auto suzanne = renderer->load_mesh("suzanne.obj");

    while(!window->closing()) {
        renderer->render(suzanne, { .position = Vec3f::zero });
        renderer->present();

        window->pull_events();
    }

    GLFWContext::terminate();// this should be moved somewhere else

    return 0;
}

