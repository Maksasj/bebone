#define BEBONE_TYPES_MATRIX_COLUMN_MAJOR_ORDER
#define BEBONE_TYPES_MATRIX4X4_PROJECTION_MATRIX_INVERSE_Y_AXIS
#include "bebone/bebone.h"

using namespace bebone::core;
using namespace bebone::gfx;
using namespace bebone::renderer;

struct Handles { u32 camera_handle, transform_handle; };

// Todo make this nicer
const auto vertex_descriptions = VulkanPipelineVertexInputStateTuple {
    .binding_descriptions = {
        { 0, sizeof(Vertex), VK_VERTEX_INPUT_RATE_VERTEX }
    },
    .attribute_descriptions = {
        { 0, 0, VK_FORMAT_R32G32B32_SFLOAT, offsetof(Vertex, position) },
        { 1, 0, VK_FORMAT_R32G32B32_SFLOAT, offsetof(Vertex, normal) },
        { 2, 0, VK_FORMAT_R32G32_SFLOAT,    offsetof(Vertex, texcoord) },
    }
};

const vector<Vertex> cube_vertices {
    {{-1.0, -1.0,  1.0},   {1.0f, 1.0f, 1.0f}, {0.0f, 0.0f}},
    {{ 1.0, -1.0,  1.0},   {1.0f, 1.0f, 0.0f}, {0.0f, 0.0f}},
    {{ 1.0,  1.0,  1.0},   {1.0f, 0.0f, 1.0f}, {0.0f, 0.0f}},
    {{-1.0,  1.0,  1.0},   {1.0f, 0.0f, 0.0f}, {0.0f, 0.0f}},
    {{-1.0, -1.0, -1.0},   {0.0f, 1.0f, 1.0f}, {0.0f, 0.0f}},
    {{ 1.0, -1.0, -1.0},   {0.0f, 1.0f, 0.0f}, {0.0f, 0.0f}},
    {{ 1.0,  1.0, -1.0},   {0.0f, 0.0f, 1.0f}, {0.0f, 0.0f}},
    {{-1.0,  1.0, -1.0},   {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f}}
};

const vector<u32> cube_indices {
    0, 1, 2, 2, 3, 0,
    1, 5, 6, 6, 2, 1,
    7, 6, 5, 5, 4, 7,
    4, 0, 3, 3, 7, 4,
    4, 5, 1, 1, 0, 4,
    3, 2, 6, 6, 7, 3
};

const std::vector<Vertex> quad_vertices {
    {{0.5f,  0.5f, 0.0f},    {1.0f, 0.0f, 0.0f},   {1.0f, 1.0f}},
    {{0.5f, -0.5f, 0.0f},    {0.0f, 1.0f, 0.0f},   {1.0f, 0.0f}},
    {{-0.5f, -0.5f,0.0f},   {0.0f, 0.0f, 1.0f},   {0.0f, 0.0f}},
    {{-0.5f,  0.5f,0.0f},   {1.0f, 1.0f, 0.0f},   {0.0f, 1.0f}}
};

const std::vector<u32> quad_indices {
    0, 1, 3,
    1, 2, 3
};

int main() {
    GLFWContext::init();

    auto window = WindowFactory::create_window("4. Vulkan 3d cube example", 800, 600, GfxAPI::Vulkan);

    auto instance = VulkanInstance::create_instance();
    auto device = instance->create_device(window);
    auto swap_chain = device->create_swap_chain(window);

    auto pipeline_manager = device->create_pipeline_manager();

    auto geometry_pipeline = pipeline_manager->create_pipeline(
        device, swap_chain, "main.vert.glsl", "main.frag.glsl",
        { VulkanConstRange::common(sizeof(Handles), 0) },
        { { BindlessUniform, 0}, { BindlessUniform, 1 } },
        { .vertex_input_state = { .vertex_descriptions = vertex_descriptions }, .rasterization_state = { .front_face = VK_FRONT_FACE_CLOCKWISE } }
    );

    auto blur_pipeline = pipeline_manager->create_pipeline(
        device, swap_chain, "blur.vert.glsl", "blur.frag.glsl",
        { },
        { { BindlessSampler, 0} },
        { .vertex_input_state = { .vertex_descriptions = vertex_descriptions }, .rasterization_state = { .front_face = VK_FRONT_FACE_COUNTER_CLOCKWISE } }
    );

    auto quad_vb = device->create_buffer_memory_from(quad_vertices);
    auto quad_eb = device->create_buffer_memory_from(quad_indices);

    auto t_ubo = device->create_buffer_memorys(sizeof(Mat4f), 3);
    auto c_ubo = device->create_buffer_memorys(sizeof(Mat4f), 3);

    auto t_handles = geometry_pipeline.bind_uniform_buffer(device, t_ubo, 0);
    auto c_handles = geometry_pipeline.bind_uniform_buffer(device, c_ubo, 1);

    auto command_buffer_pool = device->create_command_buffer_pool();
    auto command_buffers = command_buffer_pool->create_command_buffers(device, 3);

    auto transform = Transform {};
    auto camera = Mat4f::translation(Vec3f(0, 0, 5)) * Mat4f::perspective(1, window->get_aspect(), 0.1f, 100.0f);

    for(auto& ubo : c_ubo)
        ubo.upload_data(device, &camera, sizeof(Mat4f ));

    while (!window->closing()) {
        transform.rotation.x += 0.001f;
        transform.rotation.z -= 0.001f;

        GLFWContext::poll_events();

        uint32_t frame;
        if(!swap_chain->acquire_next_image(device, &frame).is_ok())
            continue;

        auto mat = transform.final_matrix();
        t_ubo[frame].upload_data(device, &mat, sizeof(Mat4f));

        auto handles = Handles { static_cast<u32>(c_handles[frame]), static_cast<u32>(t_handles[frame]) };

        auto& cmd = *command_buffers[frame];

        cmd.begin_record();

        /*
        cmd.begin_render_pass(swap_chain, frame);
        cmd.set_viewport(0, 0, window->get_width(), window->get_height());
        cmd.bind_managed_pipeline(geometry_pipeline, frame);
        cmd.push_constant(geometry_pipeline.layout, sizeof(Handles), 0, &handles);

        cmd.bind_vertex_buffer(quad_vb);
        cmd.bind_index_buffer(quad_eb);

        cmd.draw_indexed(quad_indices.size());
        cmd.end_render_pass();
        */

        cmd.begin_render_pass(swap_chain, frame);
        cmd.set_viewport(0, 0, window->get_width(), window->get_height());
        cmd.bind_managed_pipeline(blur_pipeline, frame);
        cmd.bind_vertex_buffer(quad_vb);
        cmd.bind_index_buffer(quad_eb);
        cmd.draw_indexed(quad_indices.size());
        cmd.end_render_pass();

        cmd.end_record();

        if(!swap_chain->submit_command_buffers(device, command_buffers[frame], &frame).is_ok()) // Todo check if window is resized
            continue;
    }

    instance->destroy();

    GLFWContext::terminate();

    return 0;
}
