#include "bebone/bebone.h"

using namespace bebone::renderer;
using namespace bebone::gfx;

int main() {
    auto window = WindowFactory::create_window("3. Renderer mesh", 800, 600, Vulkan, { .enable_resize = true });
    auto renderer = RendererFactory::create_renderer(window);

    auto mesh = renderer->load_mesh("suzanne.obj");
    auto material = MaterialHandle(0);

    while(!window->closing()) {
        renderer->render(mesh, material, { .position = Vec3f::zero });
        renderer->present();

        window->pull_events();
    }

    return 0;
}

