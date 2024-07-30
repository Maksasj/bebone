#include "bebone/bebone.h"

using namespace bebone::renderer;
using namespace bebone::gfx;

int main() {
    GLFWContext::init(); // this should be moved somewhere else

    auto window = WindowFactory::create_window("1. Renderer hello triangle", 800, 600, Vulkan, { .enable_resize = true });
    auto renderer = RendererFactory::create_renderer(window);

    const auto vertices = std::vector<Vertex> {
        {{-0.5f, -0.5f, 0.0f},  Vec3f::right, { 1.0, 0.0 }},
        {{0.5f, -0.5f, 0.0f}, Vec3f::up,    { 0.0, 1.0 }},
        {{0.0f,  0.5f, 0.0f} , Vec3f::forward,{ 1.0, 1.0 }},
    };

    const auto indices =  std::vector<u32> { 0, 1, 2 };

    auto mesh = renderer->create_mesh(vertices, indices);
    auto material = MaterialHandle(0);

    while(!window->closing()) {
        renderer->render(mesh, material, { .position = {
            0, sinf(static_cast<f32>(Time::get_seconds_elapsed())), 0,
        }});

        renderer->render(mesh, material, { .position = {
            0, 0, 0,
        }});

        renderer->render(mesh, material, { .position = {
            0, 0, 2,
        }});

        for(int i = 0; i < 5; ++i) {
            renderer->render(mesh, material, { .position = {
                static_cast<f32>(i), 1, 2,
            }});
        }

        renderer->present();
        window->pull_events();
    }

    GLFWContext::terminate();// this should be moved somewhere else

    return 0;
}
