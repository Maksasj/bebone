#include "bebone/bebone.h"

using namespace bebone::renderer;
using namespace bebone::gfx;

int main() {
    GLFWContext::init(); // this should be moved somewhere else

    auto window = WindowFactory::create_window("3. Renderer mesh", 800, 600, Vulkan, { .enable_resize = true });
    auto renderer = RendererFactory::create_renderer(window);

    auto mesh = renderer->load_mesh("suzanne.obj");
    auto material = std::shared_ptr<IMaterial> {};

    auto suzanne = renderer->create_model(mesh, material);

    while(!window->closing()) {
        renderer->render(suzanne, { .position = Vec3f::zero });
        renderer->present();

        window->pull_events();
    }

    GLFWContext::terminate();// this should be moved somewhere else

    return 0;
}

