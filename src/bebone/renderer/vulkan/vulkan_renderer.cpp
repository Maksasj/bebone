#include "vulkan_renderer.h"

namespace bebone::renderer {
    VulkanRenderer::VulkanRenderer(std::shared_ptr<gfx::Window>& window) : IRenderer(Vulkan), window(window) {
        instance = VulkanInstance::create_instance();
        device = instance->create_device(window);
        swap_chain = device->create_swap_chain(window);

        // Create default render graph
        render_graph = std::make_shared<PBRRenderGraph>("pbr_render_graph", create_render_graph_impl());
        render_graph->assemble();

        window->add_listener([&](WindowSizeEvent event) {
            handle_resize({ event.width, event.height });
        });
    }

    VulkanRenderer::~VulkanRenderer() {
        instance->destroy();
    }

    void VulkanRenderer::handle_resize(const Vec2i& new_size) {
        /*
        device->wait_idle();
        device->destroy_all(swap_chain);
        device->collect_garbage();

        swap_chain = device->create_swap_chain(window);

        render_graph = create_render_graph("my_graph");
        */
    }

    MeshHandle VulkanRenderer::load_mesh(const std::string& file_path) {
        auto loader = std::make_shared<OBJMeshLoader>(std::make_shared<VulkanTriangleMeshBuilder>(*device));
        auto mesh = loader->load_from_file(file_path);
        mesh_pool.push_back(mesh);
        return { mesh_pool.size() - 1 };
    }

    MeshHandle VulkanRenderer::create_mesh(const std::vector<Vertex>& vertices, const std::vector<u32>& indicies) {
        auto mesh = std::make_shared<VulkanTriangleMesh>(*device, vertices, indicies);
        mesh_pool.push_back(mesh);
        return { mesh_pool.size() - 1 };
    }

    void VulkanRenderer::render(const MeshHandle& handle, const Transform& transform) {
        std::ignore = transform;

        // Todo
        auto pass = static_pointer_cast<IRenderQueuePass>(render_graph->get_render_pass("gpass").value());

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

    std::shared_ptr<IRenderGraphImpl> VulkanRenderer::create_render_graph_impl() {
        return std::make_shared<VulkanRenderGraphImpl>(device, swap_chain);
    }
}
