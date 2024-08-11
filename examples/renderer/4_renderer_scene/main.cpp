#include "bebone/bebone.h"

using namespace bebone::renderer;
using namespace bebone::gfx;

int main() {
    auto window = WindowFactory::create_window("4. Renderer scene", 800, 600, Vulkan, { .enable_resize = true });
    auto renderer = RendererFactory::create_renderer(window);

    auto suzanne = renderer->load_mesh("suzanne.obj");

    PBRMaterialProperties properties {
        .albedo = renderer->load_texture("01-uv-texture.png"),
        .height = renderer->load_texture("used-stainless-steel2_height.png"),
        .metallic = renderer->load_texture("used-stainless-steel2_metallic.png"),
        .roughness = renderer->load_texture("used-stainless-steel2_roughness.png")
    };

    auto material = renderer->create_material(&properties, sizeof(properties));

    auto quad = renderer->gen_mesh<QuadMeshGenerator>(2.0f, 2.0f, Vec3f::back);
    auto plate = renderer->gen_mesh<CubeMeshGenerator>(2.0f, 2.0f, 2.0f);
    auto sphere = renderer->gen_mesh<UVSphereMeshGenerator>(2.0f, 64, 64);

    while(!window->closing()) {
        renderer->render(suzanne, material, Vec3f::zero);
        renderer->render(suzanne, material, Vec3f(3.0f, 0.0f, 0.0f));
        renderer->render(quad, material, Vec3f(0.0f, 4.0f, 0.0f));
        renderer->render(plate, material, Vec3f(0.0f, -4.0f, 0.0f));
        renderer->render(sphere, material, Vec3f(8.0f, 8.0f, 8.0f));

        renderer->present();
        window->pull_events();
    }

    return 0;
}

