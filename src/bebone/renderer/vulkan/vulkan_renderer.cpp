#include "vulkan_renderer.h"

namespace bebone::renderer {
    VulkanRenderer::VulkanRenderer(std::shared_ptr<gfx::Window>& window) : IRenderer(Vulkan), window(window) {
        instance = VulkanInstance::create_instance();
        device = instance->create_device(window);
        swap_chain = device->create_swap_chain(window);

        // Create default render graph
        render_graph = create_render_graph("my_graph");

        auto pass_factory = render_graph->create_pass_factory();
        auto resource_factory = render_graph->create_resource_factory();

        auto geometry_texture = resource_factory->create_texture_resource("geometry_texture");
        render_graph->add_resource(geometry_texture);

        auto geometry_depth = resource_factory->create_depth_resource("geometry_depth");
        render_graph->add_resource(geometry_depth);

        auto geometry = pass_factory->create_deferred_g_pass("geometry", { 800, 600 });
        geometry->plug_output("texture", geometry_texture);
        geometry->plug_output("depth", geometry_depth);
        render_graph->add_pass(geometry);

        auto present = pass_factory->create_present_pass("present", { 800, 600 });
        present->plug_input("texture", geometry_texture);
        render_graph->add_pass(present);

        render_graph->assemble();

        window->add_listener([&](WindowSizeEvent event) {
            handle_resize({ event.width, event.height });
        });
    }

    VulkanRenderer::~VulkanRenderer() {
        instance->destroy();
    }

    void VulkanRenderer::handle_resize(const Vec2i& new_size) {
        device->wait_idle();
        device->destroy_all(swap_chain);
        device->collect_garbage();

        swap_chain = device->create_swap_chain(window);

        render_graph = create_render_graph("my_graph");

        auto pass_factory = render_graph->create_pass_factory();
        auto resource_factory = render_graph->create_resource_factory();

        auto geometry_texture = resource_factory->create_texture_resource("geometry_texture");
        render_graph->add_resource(geometry_texture);

        auto geometry_depth = resource_factory->create_depth_resource("geometry_depth");
        render_graph->add_resource(geometry_depth);

        auto geometry = pass_factory->create_deferred_g_pass("geometry", { new_size.x, new_size.y });
        geometry->plug_output("texture", geometry_texture);
        geometry->plug_output("depth", geometry_depth);
        render_graph->add_pass(geometry);

        auto present = pass_factory->create_present_pass("present", { new_size.x, new_size.y });
        present->plug_input("texture", geometry_texture);
        render_graph->add_pass(present);

        render_graph->assemble();
    }

    MeshHandle VulkanRenderer::create_mesh(const std::vector<Vertex>& vertices, const std::vector<u32>& indicies) {
        auto mesh = std::make_shared<VulkanTriangleMesh>(*device, vertices, indicies);
        mesh_pool.push_back(mesh);
        return { mesh_pool.size() - 1 };
    }

    void VulkanRenderer::render(const MeshHandle& handle, const Transform& transform) {
        std::ignore = transform;

        auto pass = static_pointer_cast<IRenderQueuePass>(render_graph->get_render_pass("geometry").value());

        pass->submit_task([&](ICommandEncoder* encoder) {
            auto cmd = static_cast<VulkanCommandEncoder*>(encoder)->get_command_buffer();

            auto mesh = mesh_pool[handle.index];

            mesh_pool[handle.index]->bind(encoder);
            cmd->draw_indexed(mesh->triangle_count());
        });
    }

    void VulkanRenderer::present() {
        render_graph->record();
        render_graph->submit();
    }

    std::shared_ptr<IRenderGraph> VulkanRenderer::create_render_graph(const std::string& name) {
        auto impl = std::make_shared<VulkanRenderGraphImpl>(device, swap_chain);
        return std::make_shared<IRenderGraph>(name, static_pointer_cast<IRenderGraphImpl>(impl));
    }
}
