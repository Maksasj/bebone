#include "bebone/bebone.h"

using namespace bebone::core;
using namespace bebone::gfx;
using namespace bebone::renderer;

struct GeometryHandles { VulkanBindlessBufferHandle camera_handle, transform_handle; };
struct PostHandles { VulkanBindlessTextureHandle geometry_texture, blur_texture; };

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

int main() {
    auto window = WindowFactory::create_window("4. Vulkan bloom example", 800, 600, GfxAPI::Vulkan);

    auto instance = VulkanInstance::create_instance();
    auto device = instance->create_device(window);
    auto swap_chain = device->create_swap_chain(window);
    auto command_buffers = device->create_command_buffers(3);

    auto pipeline_manager = device->create_pipeline_manager();

    // Geometry pass
    auto geometry_render_pass = device->create_render_pass({800, 600}, {
        VulkanAttachmentDesc::color2D({ 800,600 }, { .format = VK_FORMAT_R32G32B32A32_SFLOAT }),
        VulkanAttachmentDesc::color2D({ 800,600 }, { .format = VK_FORMAT_R32G32B32A32_SFLOAT }),
        VulkanAttachmentDesc::depth2D({ 800,600 }, { .format = device->find_depth_format() }),
    });

    auto geometry_render_target = device->create_render_target(geometry_render_pass);

    auto geometry_pipeline = pipeline_manager->create_pipeline(
        device, geometry_render_pass, "geometry.vert.glsl", "geometry.frag.glsl",
        { .vertex_input_state = { .vertex_descriptions = vertex_descriptions } }
    );

    // Blur render pass
    auto blur_render_pass = device->create_render_pass({800, 600}, {
        VulkanAttachmentDesc::color2D({800, 600}, {.format = VK_FORMAT_R32G32B32A32_SFLOAT })
    });

    auto blur_render_target = device->create_render_target(blur_render_pass);

    auto blur_pipeline = pipeline_manager->create_pipeline(
        device, blur_render_pass, "blur.vert.glsl", "blur.frag.glsl",
        { .vertex_input_state = { .vertex_descriptions = vertex_descriptions } }
    );

    auto blur_texture_handles = pipeline_manager->bind_attachments(device, geometry_render_target->get_color_attachment(0));

    // Post pipeline
    auto post_pipeline = pipeline_manager->create_pipeline(
        device, swap_chain->render_pass, "post.vert.glsl", "post.frag.glsl",
        { .vertex_input_state = { .vertex_descriptions = vertex_descriptions } }
    );

    auto post_geometry_texture_handles = pipeline_manager->bind_attachments(device, geometry_render_target->get_color_attachment(0));
    auto post_geometry_grayscale_texture_handles = pipeline_manager->bind_attachments(device, geometry_render_target->get_color_attachment(1));
    auto post_blur_texture_handles = pipeline_manager->bind_attachments(device, blur_render_target->get_color_attachment(0));

    auto cube_generator = std::make_shared<CubeMeshGenerator>(1.0f, 1.0f, 1.0f);
    auto quad_generator = std::make_shared<QuadMeshGenerator>(1.0f, 1.0f);

    auto cube_mesh = static_pointer_cast<VulkanTriangleMeshImpl>(cube_generator->generate(std::make_shared<VulkanTriangleMeshBuilder>(*device))->get_impl());
    auto quad_mesh = static_pointer_cast<VulkanTriangleMeshImpl>(quad_generator->generate(std::make_shared<VulkanTriangleMeshBuilder>(*device))->get_impl());

    auto transform = Transform {};
    auto camera = Mat4f::perspective(1, window->get_aspect(), 0.1f, 100.0f) * Mat4f::translation(Vec3f(0, 0, 5));

    auto c_ubo = device->create_buffer_memorys(sizeof(Mat4f), 3);
    for(auto& ubo : c_ubo)
        ubo->upload_data(device, &camera, sizeof(Mat4f));
    auto c_handles = pipeline_manager->bind_uniform_buffers(device, c_ubo);

    auto t_ubo = device->create_buffer_memorys(sizeof(Mat4f), 3);
    auto t_handles = pipeline_manager->bind_uniform_buffers(device, t_ubo);

    while (!window->closing()) {
        transform.rotation.x += 0.02f;
        transform.rotation.z -= 0.02f;

        uint32_t frame;
        if(!swap_chain->acquire_next_image(device, &frame).is_ok())
            continue;

        auto mat = calculate_transform_matrix(transform);
        t_ubo[frame]->upload_data(device, &mat, sizeof(Mat4f));

        auto& cmd = command_buffers[frame];

        cmd->begin_record();
        cmd->bind_descriptor_set(pipeline_manager->get_pipeline_layout(), pipeline_manager->get_descriptor_set());

        // Render geometry
        cmd->begin_render_pass(geometry_render_target, geometry_render_pass, frame);
            // Flipped viewport
            cmd->set_viewport(0, window->get_height(), window->get_width(), -window->get_height());
            // cmd->set_viewport(0, 0, window->get_width(), window->get_height());

            cmd->bind_pipeline(geometry_pipeline);

            auto handles = GeometryHandles { c_handles[frame], t_handles[frame] };
            cmd->push_constant(pipeline_manager->get_pipeline_layout(), sizeof(GeometryHandles), 0, &handles);

            cube_mesh->bind(cmd);
            cmd->draw_indexed(cube_mesh->get_triangle_count());
        cmd->end_render_pass();

        // Blur pass
        cmd->begin_render_pass(blur_render_target, blur_render_pass, frame);
            // Flipped viewport
            cmd->set_viewport(0, window->get_height(), window->get_width(), -window->get_height());
            // cmd->set_viewport(0, 0, window->get_width(), window->get_height());

            cmd->bind_pipeline(blur_pipeline);

            auto blur_handles = blur_texture_handles[frame];
            cmd->push_constant(pipeline_manager->get_pipeline_layout(), sizeof(VulkanBindlessTextureHandle), 0, &blur_handles);

            quad_mesh->bind(cmd);
            cmd->draw_indexed(quad_mesh->get_triangle_count());
        cmd->end_render_pass();

        // Final pass
        cmd->begin_render_pass(swap_chain);
            // Flipped viewport
            cmd->set_viewport(0, window->get_height(), window->get_width(), -window->get_height());
            // cmd->set_viewport(0, 0, window->get_width(), window->get_height());

            cmd->bind_pipeline(post_pipeline);

            auto post_handle = PostHandles { post_geometry_grayscale_texture_handles[frame], post_blur_texture_handles[frame] };
            cmd->push_constant(pipeline_manager->get_pipeline_layout(), sizeof(PostHandles), 0, &post_handle);

            quad_mesh->bind(cmd);
            cmd->draw_indexed(quad_mesh->get_triangle_count());
        cmd->end_render_pass();

        cmd->end_record();
        if(!swap_chain->submit_present_command_buffers(device, command_buffers[frame], &frame).is_ok()) // Todo check if window is resized
            continue;

        window->pull_events();
    }

    instance->destroy();

    return 0;
}
