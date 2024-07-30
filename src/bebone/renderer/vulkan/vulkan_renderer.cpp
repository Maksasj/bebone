#include "vulkan_renderer.h"

namespace bebone::renderer {
    VulkanRenderer::VulkanRenderer(
        const std::shared_ptr<gfx::Window>& window
    ) : IRenderer(Vulkan), window(window) {
        // Setup vulkan
        instance = VulkanInstance::create_instance();
        device = instance->create_device(this->window);
        swap_chain = device->create_swap_chain(this->window);

        // Create all needed managers
        program_manager = std::make_shared<VulkanProgramManager>(device);
        texture_manager = std::make_shared<VulkanTextureManager>(device, program_manager);
        mesh_manager = std::make_shared<VulkanMeshManager>(device);
        material_manager = std::make_shared<VulkanMaterialManager>(device, program_manager);

        // Create default render graph
        render_graph = create_default_render_graph(window->get_size());
        render_graph->assemble();

        // Add event listener for window resize event
        window->add_listener([&](WindowSizeEvent event) {
            resize_viewport({ event.width, event.height });
        });

        // Setup default camera
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

    std::shared_ptr<IProgramManager> VulkanRenderer::get_program_manager() const {
        return program_manager;
    }

    std::shared_ptr<ITextureManager> VulkanRenderer::get_texture_manager() const {
        return texture_manager;
    }

    std::shared_ptr<IMeshManager> VulkanRenderer::get_mesh_manager() const {
        return mesh_manager;
    }

    std::shared_ptr<IMaterialManager> VulkanRenderer::get_material_manager() const {
        return material_manager;
    }

    TextureHandle VulkanRenderer::load_texture(const std::string& file_path) {
        return texture_manager->load_texture_from_file(file_path);
    }

    MeshHandle VulkanRenderer::load_mesh(const std::string& file_path) {
        return mesh_manager->load_mesh(file_path);
    }

    MeshHandle VulkanRenderer::create_mesh(const std::vector<Vertex>& vertices, const std::vector<u32>& indicies) {
        return mesh_manager->create_mesh(vertices,indicies);
    }

    MaterialHandle VulkanRenderer::default_material() {
        return material_manager->default_material();
    }

    void VulkanRenderer::render(const MeshHandle& mesh_handle, const MaterialHandle& material_handle, const Transform& transform) {
        render_graph->submit_geometry(mesh_handle, material_handle, transform);
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
        return std::make_shared<VulkanRenderGraphImpl>(device, swap_chain, program_manager, texture_manager, mesh_manager);
    }
}
