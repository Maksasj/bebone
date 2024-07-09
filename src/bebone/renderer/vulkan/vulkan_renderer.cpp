#include "vulkan_renderer.h"

namespace bebone::renderer {
    VulkanRenderer::VulkanRenderer(std::shared_ptr<gfx::Window>& window) : IRenderer(Vulkan), window(window) {
        instance = VulkanInstance::create_instance();
        device = instance->create_device(window);
        swap_chain = device->create_swap_chain(window);

        // Create default render graph
        render_graph = std::make_shared<VulkanRenderGraph>(device, swap_chain);

        auto pass_factory = render_graph->create_pass_factory();
        auto resource_factory = render_graph->create_resource_factory();

        auto geometry_texture = resource_factory->create_texture_resource("geometry_texture");
        render_graph->add_resource(geometry_texture);

        auto geometry_depth = resource_factory->create_depth_resource("geometry_depth");
        render_graph->add_resource(geometry_depth);

        // auto geometry = pass_factory->create_geometry_pass("geometry");
        // render_graph->add_pass(geometry);

        auto present = pass_factory->create_present_pass("present");
        render_graph->add_pass(present);

        render_graph->build();
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
        /*
        auto pass = static_pointer_cast<IGeometryPass>(render_graph->get_render_pass("geometry").value());

        pass->queue_task([&](ICommandEncoder* encoder) {
            auto cmd = static_cast<VulkanCommandEncoder*>(encoder)->get_command_buffer();

            auto mesh = mesh_pool[handle.index];

            mesh_pool[handle.index]->bind(encoder);
            cmd->draw_indexed(mesh->triangle_count());
        });
        */
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
