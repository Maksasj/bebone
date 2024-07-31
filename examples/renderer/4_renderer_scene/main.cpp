#include "bebone/bebone.h"

using namespace bebone::renderer;
using namespace bebone::gfx;

int main() {
    GLFWContext::init(); // this should be moved somewhere else

    auto window = WindowFactory::create_window("4. Renderer scene", 800, 600, Vulkan, { .enable_resize = true });
    auto renderer = RendererFactory::create_renderer(window);

    auto suzanne = renderer->load_mesh("suzanne.obj");

    PBRMaterialProperties properties {
        .albedo = renderer->load_texture("used-stainless-steel2_albedo.png"),
        .height = renderer->load_texture("used-stainless-steel2_height.png"),
        .metallic = renderer->load_texture("used-stainless-steel2_metallic.png"),
        .roughness = renderer->load_texture("used-stainless-steel2_roughness.png")
    };

    auto material = renderer->create_material(&properties, sizeof(properties));

    auto plate = renderer->generate_mesh(std::make_shared<CubeMeshGenerator>(7.0f, 1.0f, 7.0f));

    while(!window->closing()) {
        renderer->render(suzanne, material, {});
        renderer->render(plate, material, { .position = Vec3f(0.0f, -3.0f, 0.0f) });

        renderer->present();
        window->pull_events();
    }

    GLFWContext::terminate();// this should be moved somewhere else

    return 0;
}

