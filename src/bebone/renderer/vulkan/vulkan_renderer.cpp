#include "vulkan_renderer.h"

namespace bebone::renderer {
    VulkanRenderer::VulkanRenderer(std::shared_ptr<gfx::Window>& window) : IRenderer(Vulkan), window(window) {
        instance = VulkanInstance::create_instance();
        device = instance->create_device(window);
        swap_chain = device->create_swap_chain(window);

        program_manager = std::make_shared<VulkanProgramManager>(device);
        texture_manager = std::make_shared<VulkanTextureManager>(device, program_manager);

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

    // Todo, probably since we use bindless textures, we can bind all texture to ALL pipelines
    // Everything should work fine
    std::shared_ptr<ITexture> VulkanRenderer::load_texture(const std::string& file_path) {
        return texture_manager->load_texture_from_file(file_path);
    }

    std::shared_ptr<IMaterial> VulkanRenderer::create_material(const std::string& albedo) {
        return std::make_shared<PBRMaterial>("pbr_material", load_texture(albedo));
    }

    std::shared_ptr<IMesh> VulkanRenderer::load_mesh(const std::string& file_path) {
        auto loader = std::make_shared<OBJMeshLoader>(std::make_shared<VulkanTriangleMeshBuilder>(*device));
        auto mesh = loader->load_from_file(file_path);
        return mesh;
    }

    std::shared_ptr<IMesh> VulkanRenderer::create_mesh(const std::vector<Vertex>& vertices, const std::vector<u32>& indicies) {
        auto mesh = std::make_shared<VulkanTriangleMesh>(*device, vertices, indicies);
        return mesh;
    }

    ModelHandle VulkanRenderer::create_model(std::shared_ptr<IMesh>& mesh, std::shared_ptr<IMaterial>& material) {
        auto model = std::make_shared<IModel>(mesh, material);
        model_pool.push_back(model);
        return { model_pool.size() - 1 };
    }

    void VulkanRenderer::render(const ModelHandle& handle, const Transform& transform) {
        auto mesh = model_pool[handle.index];
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
        return std::make_shared<VulkanRenderGraphImpl>(device, swap_chain, program_manager, texture_manager);
    }
}
