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

    auto window = WindowFactory::create_window("4. Vulkan bloom example", 800, 600, GfxAPI::Vulkan);

    auto instance = VulkanInstance::create_instance();
    auto device = instance->create_device(window);
    auto swap_chain = device->create_swap_chain(window);

    auto command_buffer_pool = device->create_command_buffer_pool();
    auto command_buffers = command_buffer_pool->create_command_buffers(device, 3);

    auto pipeline_manager = device->create_pipeline_manager();

    // Geometry pass
    auto geometry_render_pass = device->create_render_pass({
        VulkanAttachment::color({.format = VK_FORMAT_R32G32B32A32_SFLOAT })
    });

    auto geometry_textures = std::vector<std::shared_ptr<VulkanTexture>> {
        device->create_texture(command_buffer_pool, 800, 600, VK_FORMAT_R32G32B32A32_SFLOAT),
        device->create_texture(command_buffer_pool, 800, 600, VK_FORMAT_R32G32B32A32_SFLOAT),
        device->create_texture(command_buffer_pool, 800, 600, VK_FORMAT_R32G32B32A32_SFLOAT)
    };

    auto geometry_framebuffers = std::vector<std::shared_ptr<VulkanFramebuffer>> {
        device->create_framebuffer({ geometry_textures[0]->view }, geometry_render_pass, {800, 600}),
        device->create_framebuffer({ geometry_textures[1]->view }, geometry_render_pass, {800, 600}),
        device->create_framebuffer({ geometry_textures[2]->view }, geometry_render_pass, {800, 600})
    };

    auto geometry_pipeline = pipeline_manager->create_pipeline(
        device, geometry_render_pass, "geometry.vert.glsl", "geometry.frag.glsl",
        { VulkanConstRange::common(sizeof(Handles), 0) },
        { { BindlessUniform, 0}, { BindlessUniform, 1 } },
        { .vertex_input_state = { .vertex_descriptions = vertex_descriptions }, .rasterization_state = { .front_face = VK_FRONT_FACE_COUNTER_CLOCKWISE } }
    );

    /*
    // Blur render pass
    auto blur_render_pass = device->create_render_pass({
        VulkanAttachment::color({.format = VK_FORMAT_R32G32B32A32_SFLOAT })
    });

    auto blur_textures = std::vector<std::shared_ptr<VulkanTexture>> {
        device->create_texture(command_buffer_pool, 800, 600, VK_FORMAT_R32G32B32A32_SFLOAT),
        device->create_texture(command_buffer_pool, 800, 600, VK_FORMAT_R32G32B32A32_SFLOAT),
        device->create_texture(command_buffer_pool, 800, 600, VK_FORMAT_R32G32B32A32_SFLOAT)
    };

    auto blur_framebuffers = std::vector<std::shared_ptr<VulkanFramebuffer>> {
        device->create_framebuffer({ blur_textures[0]->view }, blur_render_pass, {800, 600}),
        device->create_framebuffer({ blur_textures[1]->view }, blur_render_pass, {800, 600}),
        device->create_framebuffer({ blur_textures[2]->view }, blur_render_pass, {800, 600})
    };

    auto blur_pipeline = pipeline_manager->create_pipeline(
        device, blur_render_pass, "blur.vert.glsl", "blur.frag.glsl",
        { },
        { { BindlessSampler, 0} },
        { .vertex_input_state = { .vertex_descriptions = vertex_descriptions }, .rasterization_state = { .front_face = VK_FRONT_FACE_COUNTER_CLOCKWISE } }
    );
    */

    // Post pipeline
    auto post_pipeline = pipeline_manager->create_pipeline(
        device, swap_chain->render_target->render_pass, "post.vert.glsl", "post.frag.glsl",
        {  },
        { { BindlessSampler, 0} },
        { .vertex_input_state = { .vertex_descriptions = vertex_descriptions }, .rasterization_state = { .front_face = VK_FRONT_FACE_COUNTER_CLOCKWISE } }
    );

    auto cube_vb = device->create_buffer_memory_from(cube_vertices);
    auto cube_eb = device->create_buffer_memory_from(cube_indices);

    auto quad_vb = device->create_buffer_memory_from(quad_vertices);
    auto quad_eb = device->create_buffer_memory_from(quad_indices);

    auto t_ubo = device->create_buffer_memorys(sizeof(Mat4f), 3);
    auto c_ubo = device->create_buffer_memorys(sizeof(Mat4f), 3);

    auto transform = Transform {};
    auto camera = Mat4f::translation(Vec3f(0, 0, 5)) * Mat4f::perspective(1, window->get_aspect(), 0.1f, 100.0f);

    for(auto& ubo : c_ubo)
        ubo.upload_data(device, &camera, sizeof(Mat4f));

    auto t_handles = geometry_pipeline.bind_uniform_buffer(device, t_ubo, 0);
    auto c_handles = geometry_pipeline.bind_uniform_buffer(device, c_ubo, 1);

    auto geometry_texture_handles = std::vector<VulkanBindlessHandle> {};
    geometry_texture_handles.push_back(post_pipeline.bind_texture(device, geometry_textures[0], 0)[0]);
    geometry_texture_handles.push_back(post_pipeline.bind_texture(device, geometry_textures[1], 0)[0]);
    geometry_texture_handles.push_back(post_pipeline.bind_texture(device, geometry_textures[2], 0)[0]);

   // for(auto& g : geometry_textures) {
   //     geometry_texture_handles.push_back();
   // }

    /*
    for(auto t : blur_textures) {
        t->image->transition_layout(
            *command_buffer_pool,
            *device,
            VK_IMAGE_LAYOUT_UNDEFINED,
            VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL);

        t->image->transition_layout(
            *command_buffer_pool,
            *device,
            VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL,
            VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL);

        std::ignore = post_pipeline.bind_texture(device, t, 0);
    }
    */

    while (!window->closing()) {
        transform.rotation.x += 0.001f;
        transform.rotation.z -= 0.001f;

        uint32_t frame;
        if(!swap_chain->acquire_next_image(device, &frame).is_ok())
            continue;

        auto mat = transform.final_matrix();
        t_ubo[frame].upload_data(device, &mat, sizeof(Mat4f));

        auto& cmd = *command_buffers[frame];

        cmd.begin_record();

        // Render geometry
        cmd.begin_render_pass(
            geometry_framebuffers[frame],
            geometry_render_pass,
            swap_chain->extent);

            cmd.set_viewport(0, 0, window->get_width(), window->get_height());
            cmd.bind_managed_pipeline(geometry_pipeline, frame);

            auto handles = Handles { static_cast<u32>(c_handles[frame]), static_cast<u32>(t_handles[frame]) };
            cmd.push_constant(geometry_pipeline.layout, sizeof(Handles), 0, &handles);

            cmd.bind_vertex_buffer(cube_vb);
            cmd.bind_index_buffer(cube_eb);
            cmd.draw_indexed(cube_indices.size());
        cmd.end_render_pass();

        // Final pass
        cmd.begin_render_pass(
            swap_chain->render_target->framebuffers[frame],
            swap_chain->render_target->render_pass,
            swap_chain->extent);

            cmd.set_viewport(0, 0, window->get_width(), window->get_height());
            cmd.bind_managed_pipeline(post_pipeline, frame);

            cmd.bind_vertex_buffer(quad_vb);
            cmd.bind_index_buffer(quad_eb);
            cmd.draw_indexed(quad_indices.size());
        cmd.end_render_pass();

        /*
        cmd.begin_render_pass(
            blur_framebuffers[frame],
            render_pass,
            swap_chain->extent);

            cmd.set_viewport(0, 0, window->get_width(), window->get_height());
            cmd.bind_managed_pipeline(blur_pipeline, frame);
            cmd.bind_vertex_buffer(quad_vb);
            cmd.bind_index_buffer(quad_eb);
            cmd.draw_indexed(quad_indices.size());
        cmd.end_render_pass();

        cmd.begin_render_pass(
            swap_chain->render_target->blur_framebuffers[frame],
            swap_chain->render_target->render_pass,
            swap_chain->extent);

            cmd.set_viewport(0, 0, window->get_width(), window->get_height());
            cmd.bind_managed_pipeline(geometry_pipeline, frame);
            cmd.push_constant(geometry_pipeline.layout, sizeof(Handles), 0, &handles);
            cmd.bind_vertex_buffer(cube_vb);
            cmd.bind_index_buffer(cube_eb);
            cmd.draw_indexed(cube_indices.size());
        cmd.end_render_pass();
        */

        cmd.end_record();

        if(!swap_chain->submit_present_command_buffers(device, command_buffers[frame], &frame).is_ok()) // Todo check if window is resized
            continue;

        GLFWContext::poll_events();
    }

    instance->destroy();

    GLFWContext::terminate();

    return 0;
}
