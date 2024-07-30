#include "bebone/bebone.h"

using namespace bebone::renderer;
using namespace bebone::gfx;

int main() {
    GLFWContext::init(); // this should be moved somewhere else

    auto window = WindowFactory::create_window("4. Renderer scene", 800, 600, Vulkan, { .enable_resize = true });
    auto renderer = RendererFactory::create_renderer(window);

    auto mesh = renderer->load_mesh("suzanne.obj");
    auto material = MaterialHandle(0);

    while(!window->closing()) {

        for(f32 i = 0; i < 5; i += 1.0f) {
            for(f32 j = 0; j < 5; j += 1.0f) {
                renderer->render(mesh, material, { .position = Vec3f((i - 2.5f)  * 3, 0, (j - 2.5f) * 3) });
            }
        }

        renderer->present();

        window->pull_events();
    }

    GLFWContext::terminate();// this should be moved somewhere else

    return 0;
}

