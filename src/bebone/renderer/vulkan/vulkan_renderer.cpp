#include "vulkan_renderer.h"

namespace bebone::renderer {
    // Todo move this outside
    const auto vertex_descriptions = bebone::gfx::VulkanPipelineVertexInputStateTuple {
        .binding_descriptions = {
            { 0, sizeof(Vertex), VK_VERTEX_INPUT_RATE_VERTEX }
        },
        .attribute_descriptions = {
            { 0, 0, VK_FORMAT_R32G32B32_SFLOAT, offsetof(Vertex, position) },
            { 1, 0, VK_FORMAT_R32G32B32_SFLOAT, offsetof(Vertex, normal) },
            { 2, 0, VK_FORMAT_R32G32_SFLOAT,    offsetof(Vertex, texcoord) },
        }
    };

    VulkanRenderer::VulkanRenderer(std::shared_ptr<gfx::Window>& window) : IRenderer(Vulkan), window(window) {
        instance = VulkanInstance::create_instance();
        device = instance->create_device(window);
        swap_chain = device->create_swap_chain(window);

        pipeline_manager = device->create_pipeline_manager();

        command_buffers = device->create_command_buffers(3);

        auto vert_shader_module = device->create_shader_module("#version 450 core\n"
                                                               "#extension GL_EXT_nonuniform_qualifier : enable\n"
                                                               "\n"
                                                               "layout (location = 0) in vec3 position;\n"
                                                               "layout (location = 1) in vec3 normal;\n"
                                                               "layout (location = 2) in vec2 texcoord;\n"
                                                               "\n"
                                                               "layout (location = 0) out vec3 out_normal;\n"
                                                               "layout (location = 1) out vec2 out_texcoord;\n"
                                                               "\n"
                                                               "void main() {\n"
                                                               "    gl_Position = vec4(position, 1.0);\n"
                                                               "\n"
                                                               "    out_normal = normal;\n"
                                                               "    out_texcoord = texcoord;\n"
                                                               "}", VertexShader);

        auto frag_shader_module = device->create_shader_module("#version 450 core\n"
                                                               "#extension GL_EXT_nonuniform_qualifier : enable\n"
                                                               "\n"
                                                               "layout (location = 0) in vec3 normal;\n"
                                                               "layout (location = 1) in vec2 texcoord;\n"
                                                               "\n"
                                                               "layout (location = 0) out vec4 out_color;\n"
                                                               "\n"
                                                               "void main() {\n"
                                                               "   out_color = vec4(texcoord, 1.0, 1.0);\n"
                                                               "}", FragmentShader);

        // Post pipeline
        pipeline = pipeline_manager->create_pipeline(
            device, swap_chain->render_pass, vert_shader_module, frag_shader_module,
            { },
            { { BindlessSampler, 0} },
            { .vertex_input_state = { .vertex_descriptions = vertex_descriptions }, .rasterization_state = { .front_face = VK_FRONT_FACE_COUNTER_CLOCKWISE } }
        );

        /*
        auto graph = std::make_shared<VulkanRenderGraph>();

        auto factory = std::make_shared<VulkanRenderPassFactory>();

        auto geometry = factory->create_geometry_pass("geometry");


        auto geometry_texture = create_texture();
        graph->append_resource(geometry_texture);

        auto depth_texture = create_texture();
        graph->append_resource(depth_texture);

        auto geometry = std::make_shared<VulkanGeometryPass>("geometry");
        geometry->link_resource("geometry_texture", "$.geometry_texture");
        geometry->link_resource("depth_texture", "$.depth_texture");
        graph->append_pass(geometry);

        auto present = std::make_shared<ISwapChainPresentPass>("present");
        present->link_resource("present_texture", "geometry.geometry_texture")

        graph->append_pass(present);
        */
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
        render_queue.push(mesh_pool[handle.index]);

        std::ignore = handle;
        std::ignore = transform;
    }

    void VulkanRenderer::render(const ModelHandle& handle, const Transform& transform) {
        std::ignore = handle;
        std::ignore = transform;
    }

    void VulkanRenderer::present() {
        uint32_t frame;
        if(!swap_chain->acquire_next_image(device, &frame).is_ok())
            return;

        auto& cmd = command_buffers[frame];
        VulkanCommandEncoder encoder(cmd);

        cmd->begin_record();

        cmd->begin_render_pass(swap_chain);
            cmd->set_viewport(0, 0, window->get_width(), window->get_height());
            cmd->bind_managed_pipeline(pipeline.value(), frame);

            for (; !render_queue.empty(); render_queue.pop()) {
                auto mesh = render_queue.front();
                mesh->bind(&encoder);
                cmd->draw_indexed(mesh->triangle_count());
            }
        cmd->end_render_pass();

        cmd->end_record();

        if(!swap_chain->submit_present_command_buffers(device, command_buffers[frame], &frame).is_ok()) // Todo check if window is resized
            return;
    }
}
