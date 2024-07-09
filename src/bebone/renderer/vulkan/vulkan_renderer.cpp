#include "vulkan_renderer.h"

namespace bebone::renderer {
    VulkanRenderer::VulkanRenderer(std::shared_ptr<gfx::Window>& window) : IRenderer(Vulkan), window(window) {
        instance = VulkanInstance::create_instance();
        device = instance->create_device(window);
        swap_chain = device->create_swap_chain(window);

        /*
        pipeline_manager = device->create_pipeline_manager();

        command_buffers = device->create_command_buffers(3);
        */

        render_graph = std::make_shared<VulkanRenderGraph>(device, swap_chain);
        auto factory = render_graph->create_pass_factory();

        // auto geometry = factory->create_geometry_pass("geometry");
        // render_graph->append_pass(geometry);

        auto present = factory->create_present_pass("present");
        render_graph->append_pass(present);

        // auto present = std::make_shared<ISwapChainPresentPass>("present");
        // present->link_resource("present_texture", "geometry.geometry_texture")
    }

    VulkanRenderer::~VulkanRenderer() {
        instance->destroy();
    }

    SpriteHandle VulkanRenderer::load_sprite(const std::string& file_path) {

    }

    ModelHandle VulkanRenderer::load_model(const std::string& file_path) {

    }

    MeshHandle VulkanRenderer::create_mesh(const std::vector<Vertex>& vertices, const std::vector<u32>& indicies) {
        auto mesh = std::make_shared<VulkanTriangleMesh>(*device, vertices, indicies);
        mesh_pool.push_back(mesh);
        return { mesh_pool.size() - 1 };
    }

    void VulkanRenderer::render(const SpriteHandle& handle, const Transform& transform) {
        std::ignore = handle;
        std::ignore = transform;
    }

    void VulkanRenderer::render(const MeshHandle& handle, const Transform& transform) {
        std::ignore = handle;
        std::ignore = transform;
    }

    void VulkanRenderer::render(const ModelHandle& handle, const Transform& transform) {
        std::ignore = handle;
        std::ignore = transform;
    }

    void VulkanRenderer::present() {
        render_graph->record();
        render_graph->submit();
    }
}
