#include "bebone/bebone.h"

using namespace bebone::renderer;
using namespace bebone::gfx;

int main() {
    GLFWContext::init(); // this should be moved somewhere else

    auto window = WindowFactory::create_window("1. Renderer hello triangle", 800, 600, Vulkan, { .enable_resize = true });
    auto renderer = RendererFactory::create_renderer(window);

    const std::vector<Vertex> vertices = {
        {{0.5f, 0.5f, 0.0f},  Vec3f::right, { 1.0, 0.0 }},
        {{0.0f, -0.5f, 0.0f}, Vec3f::up,    { 0.0, 1.0 }},
        {{-0.5f, 0.5f, 0.0f}, Vec3f::forward,{ 1.0, 1.0 }},
    };

    const std::vector<u32> indices = { 0, 1, 2 };

    MeshHandle triangle = renderer->create_mesh(vertices, indices);

    while(!window->closing()) {
        renderer->render(triangle, { .position = Vec3f::zero });
        renderer->present();

        GLFWContext::poll_events();
    }

    GLFWContext::terminate();// this should be moved somewhere else

    return 0;
}
