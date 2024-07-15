#include "vulkan_renderer.h"

namespace bebone::renderer {
    VulkanRenderer::VulkanRenderer(std::shared_ptr<gfx::Window>& window) : IRenderer(Vulkan), window(window) {
        instance = VulkanInstance::create_instance();
        device = instance->create_device(window);
        swap_chain = device->create_swap_chain(window);

        // Create default render graph
        render_graph = create_default_render_graph(window->get_size());
        render_graph->assemble();

        window->add_listener([&](WindowSizeEvent event) {
            resize_viewport({ event.width, event.height });
        });

        camera = std::make_shared<IDebugCamera>(window);
        auto pass = static_pointer_cast<IGraphicsPass>(render_graph->get_render_pass("gpass").value());
        pass->set_camera(camera);
    }

    VulkanRenderer::~VulkanRenderer() {
        instance->destroy();
    }

    void VulkanRenderer::resize_viewport(const Vec2i& new_size) {
        std::ignore = new_size;

        device->wait_idle();
        device->destroy_all(swap_chain);
        device->collect_garbage();

        swap_chain = device->create_swap_chain(window);
        render_graph = create_default_render_graph(window->get_size());
        render_graph->assemble();

        auto pass = static_pointer_cast<IGraphicsPass>(render_graph->get_render_pass("gpass").value());
        pass->set_camera(camera);
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
        auto mesh = mesh_pool[handle.index];
        render_graph->submit_geometry(mesh, transform);
    }

    void VulkanRenderer::present() {
        // Record draw commands
        render_graph->record();

        // Submit draw commands
        render_graph->submit();

        // Reset all rendering queues
        render_graph->reset();
    }

    std::shared_ptr<IRenderGraphImpl> VulkanRenderer::create_render_graph_impl() {
        return std::make_shared<VulkanRenderGraphImpl>(device, swap_chain);
    }
}
