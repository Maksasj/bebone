#include "bebone/bebone.h"

using namespace bebone::core;
using namespace bebone::gfx;

struct Vertex { Vec3f pos, color; };
struct Handles { VulkanBindlessBufferHandle camera_handle, transform_handle; };
struct CameraTransform { Mat4f view, proj; };
struct Transform { Mat4f transform, scale, rotation; };

const std::vector<Vertex> vertices = {
    {{-1.0, -1.0, -1.0}, {0.0f, 1.0f, 1.0f}},
    {{ 1.0, -1.0, -1.0}, {0.0f, 1.0f, 0.0f}},
    {{ 1.0,  1.0, -1.0}, {0.0f, 0.0f, 1.0f}},
    {{-1.0,  1.0, -1.0}, {0.0f, 0.0f, 0.0f}},
    {{-1.0, -1.0,  1.0}, {1.0f, 1.0f, 1.0f}},
    {{ 1.0, -1.0,  1.0}, {1.0f, 1.0f, 0.0f}},
    {{ 1.0,  1.0,  1.0}, {1.0f, 0.0f, 1.0f}},
    {{-1.0,  1.0,  1.0}, {1.0f, 0.0f, 0.0f}},
};

const std::vector<int> indices = {
    0, 1, 2, 2, 3, 0,
    1, 5, 6, 6, 2, 1,
    7, 6, 5, 5, 4, 7,
    4, 0, 3, 3, 7, 4,
    4, 5, 1, 1, 0, 4,
    3, 2, 6, 6, 7, 3
};

// Todo make this nicer
const auto vertex_descriptions = VulkanPipelineVertexInputStateTuple {
    .binding_descriptions = {
        { 0, sizeof(Vertex), VK_VERTEX_INPUT_RATE_VERTEX }
    },
    .attribute_descriptions = {
        { 0, 0, VK_FORMAT_R32G32B32_SFLOAT, offsetof(Vertex, pos) },
        { 1, 0, VK_FORMAT_R32G32B32_SFLOAT, offsetof(Vertex, color) },
    }
};

int main() {
    GLFWContext::init();

    auto window = WindowFactory::create_window("3. Vulkan 3d cube example", 800, 600, GfxAPI::Vulkan);

    auto instance = VulkanInstance::create_instance();
    auto device = instance->create_device(window);
    auto swap_chain = device->create_swap_chain(window);

    auto pipeline_manager = device->create_pipeline_manager();

    auto pipeline = pipeline_manager->create_pipeline(
        device, swap_chain->render_pass, "vert.glsl", "frag.glsl",
        { .vertex_input_state = { .vertex_descriptions = vertex_descriptions } }
    );

    auto vb = device->create_buffer_memory_from(vertices);
    auto eb = device->create_buffer_memory_from(indices);

    auto t_ubo = device->create_buffer_memorys(sizeof(Transform), 3);
    auto c_ubo = device->create_buffer_memorys(sizeof(CameraTransform), 3);

    auto t_handles = pipeline_manager->bind_uniform_buffers(device, t_ubo);
    auto c_handles = pipeline_manager->bind_uniform_buffers(device, c_ubo);

    auto command_buffer_pool = device->create_command_buffer_pool();
    auto command_buffers = command_buffer_pool->create_command_buffers(device, 3);

    auto c_transform = CameraTransform {
        Mat4f::view(Vec3f(0.0f, 0.0f, -10.0f), Vec3f::forward, Vec3f::down),
        Mat4f::perspective(1.0472, window->get_aspect(), 0.1f, 100.0f)
    };

    for(auto& ubo : c_ubo)
        ubo->upload_data(device, &c_transform, sizeof(CameraTransform));

    auto transform = Transform {
        Mat4f::translation(Vec3f::zero),
        Mat4f::scale(1.0f),
        Mat4f::identity()
    };

    f32 t = 0.0f;
    while (!window->closing()) {
        window->pull_events();
        t += Time::get_delta_time() * 0.05f;

        uint32_t frame;
        if(!swap_chain->acquire_next_image(device, &frame).is_ok())
            continue;

        transform.rotation = trait_bryan_angle_yxz(Vec3f(Time::get_seconds_elapsed(), Time::get_seconds_elapsed(), 0.0f));
        t_ubo[frame]->upload_data(device, &transform, sizeof(Transform));

        auto& cmd = *command_buffers[frame];

        cmd.begin_record();
        cmd.bind_descriptor_set(pipeline_manager->get_pipeline_layout(), pipeline_manager->get_descriptor_set());

        cmd.begin_render_pass(swap_chain);
            cmd.set_viewport(0, 0, window->get_width(), window->get_height());
            cmd.bind_pipeline(pipeline);

            auto handles = Handles { c_handles[frame], t_handles[frame] };
            cmd.push_constant(pipeline_manager->get_pipeline_layout(), sizeof(Handles), 0, &handles);

            cmd.bind_vertex_buffer(vb);
            cmd.bind_index_buffer(eb);
            cmd.draw_indexed(indices.size());
        cmd.end_render_pass();

        cmd.end_record();

        if(!swap_chain->submit_present_command_buffers(device, command_buffers[frame], &frame).is_ok()) // Todo check if window is resized
            continue;
    }

    instance->destroy();

    GLFWContext::terminate();

    return 0;
}
