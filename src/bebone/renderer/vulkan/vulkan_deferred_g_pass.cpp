#include "vulkan_deferred_g_pass.h"

static const char vulkan_deferred_g_pass_vertex_shader_code[] =
    "#version 450 core\n"
    "#extension GL_EXT_nonuniform_qualifier : enable\n"

    "layout (location = 0) in vec3 position;\n"
    "layout (location = 1) in vec3 normal;\n"
    "layout (location = 2) in vec2 texcoord;\n"

    "layout (location = 0) out vec3 out_position;\n"
    "layout (location = 1) out vec3 out_normal;\n"
    "layout (location = 2) out vec2 out_texcoord;\n"

    "layout(set = 0, binding = 0) uniform ModelUBO {\n"
    "   mat4 transforms[50];\n"
    "} modelUBO[];\n"

    "layout(set = 0, binding = 0) uniform SomeUBO {\n"
    "   mat4 transforms[50];\n"
    "} someUBO[];\n"

    "layout(binding = 1) uniform CameraUBO {\n"
    "   mat4 matrix;\n"
    "} cameraUBO [];\n"

    "layout(binding = 0) uniform MaterialUBO {\n"
    "   int albedo_handle[100];\n"
    "} materialUBO[];\n"

    "layout( push_constant ) uniform Handles {\n"
    "    int model_handle;\n"
    "    int model_instance;\n"
    "    int camera_handle;\n"
    "} handles;\n"

    "void main() {\n"
    "    mat4 model = modelUBO[handles.model_handle].transforms[handles.model_instance];\n"
    "    mat4 cam = cameraUBO[handles.camera_handle].matrix;\n"
    "    vec4 final_pos = cam * model * vec4(position, 1.0);\n"

    "    out_position = (model * vec4(position, 1.0)).xyz;\n"
    "    out_normal = normal;\n"
    "    out_texcoord = texcoord;\n"

    "    gl_Position = final_pos;\n"
    "}";

static const char vulkan_deferred_g_pass_fragment_shader_code[] =
    "#version 450 core\n"
    "#extension GL_EXT_nonuniform_qualifier : enable\n"

    "layout (location = 0) in vec3 in_position;\n"
    "layout (location = 1) in vec3 in_normal;\n"
    "layout (location = 2) in vec2 in_texcoord;\n"

    "layout (location = 0) out vec4 out_position;\n"
    "layout (location = 1) out vec4 out_normals;\n"
    "layout (location = 2) out vec4 out_albedo;\n"
    "layout (location = 3) out vec4 out_specular;\n"

    "void main() {\n"
    "   out_position = vec4(in_position, 1.0);\n"
    "   out_normals = vec4(in_normal, 1.0);\n"
    "   out_albedo = vec4(in_texcoord, 1.0, 1.0);\n"
    "   out_specular = vec4(0.0);\n"
    "}";

const auto vulkan_present_pass_vertex_descriptions = bebone::gfx::VulkanPipelineVertexInputStateTuple {
    .binding_descriptions = {
        { 0, sizeof(bebone::renderer::Vertex), VK_VERTEX_INPUT_RATE_VERTEX }
    },
    .attribute_descriptions = {
        { 0, 0, VK_FORMAT_R32G32B32_SFLOAT, offsetof(bebone::renderer::Vertex, position) },
        { 1, 0, VK_FORMAT_R32G32B32_SFLOAT, offsetof(bebone::renderer::Vertex, normal) },
        { 2, 0, VK_FORMAT_R32G32_SFLOAT,    offsetof(bebone::renderer::Vertex, texcoord) },
    }
};

namespace bebone::renderer {
    using namespace bebone::gfx;

    // Present pass
    VulkanDeferredGPass::VulkanDeferredGPass(
        const std::string& pass_name,
        const Vec2i& viewport
    ) : IDeferredGPass(pass_name, viewport) {
        queued_jobs_model.reserve(max_queued_jobs);
        queued_jobs_transform.reserve(max_queued_jobs);
    }

    void VulkanDeferredGPass::assemble(IPassAssembler* assember) {
        auto vulkan_assembler = static_cast<VulkanPassAssembler*>(assember);

        auto device = vulkan_assembler->get_device();
        auto program_manager = vulkan_assembler->get_program_manager();
        auto pipeline_manager = program_manager->get_pipeline_manager();

        auto viewport = VkExtent2D { static_cast<uint32_t>(get_viewport().x), static_cast<uint32_t>(get_viewport().y) };

        // Create render pass
        render_pass = device->create_render_pass(viewport, {
            VulkanAttachmentDesc::color2D(viewport, { .format = VK_FORMAT_R32G32B32A32_SFLOAT }), /* position */
            VulkanAttachmentDesc::color2D(viewport, { .format = VK_FORMAT_R32G32B32A32_SFLOAT }), /* normals  */
            VulkanAttachmentDesc::color2D(viewport, { .format = VK_FORMAT_R32G32B32A32_SFLOAT }), /* albedo   */
            VulkanAttachmentDesc::color2D(viewport, { .format = VK_FORMAT_R32G32B32A32_SFLOAT }), /* specular */
            VulkanAttachmentDesc::depth2D(viewport, { .format = device->find_depth_format() }),   /* depth    */
        });

        // Create shader modules
        auto vert_shader_module = device->create_shader_module(vulkan_deferred_g_pass_vertex_shader_code, VertexShader);
        auto frag_shader_module = device->create_shader_module(vulkan_deferred_g_pass_fragment_shader_code, FragmentShader);

        // Create pipeline
        auto pipeline = pipeline_manager->create_pipeline(
            device, render_pass, vert_shader_module, frag_shader_module,
            { VulkanConstRange::common(sizeof(VulkanDeferredGPassHandles), 0) },
            { { BindlessUniform, 0}, { BindlessUniform, 1 } },
            {
                .vertex_input_state = { .vertex_descriptions = vulkan_present_pass_vertex_descriptions },
                .rasterization_state = { .front_face = VK_FRONT_FACE_CLOCKWISE } // Todo
            }
        );

        // Delete shader modules and clear memory
        device->destroy_all(vert_shader_module, frag_shader_module);
        device->collect_garbage();

        auto program = program_manager->create_program(pipeline);

        // Setup render target
        auto position = static_pointer_cast<VulkanHDRTextureResource>(position_resource)->get_textures();
        auto normals = static_pointer_cast<VulkanHDRTextureResource>(normals_resource)->get_textures();
        auto albedo = static_pointer_cast<VulkanHDRTextureResource>(albedo_resource)->get_textures();
        auto specular = static_pointer_cast<VulkanHDRTextureResource>(specular_resource)->get_textures();

        auto depth = static_pointer_cast<VulkanDepthResource>(depth_resource)->get_textures();

        framebuffers = std::vector<std::shared_ptr<VulkanFramebuffer>> {
            device->create_framebuffer({ position[0]->view, normals[0]->view, albedo[0]->view, specular[0]->view, depth[0]->view }, render_pass, viewport),
            device->create_framebuffer({ position[1]->view, normals[1]->view, albedo[1]->view, specular[1]->view, depth[1]->view }, render_pass, viewport),
            device->create_framebuffer({ position[2]->view, normals[2]->view, albedo[2]->view, specular[2]->view, depth[2]->view }, render_pass, viewport)
        };

        // Create and bind model and camera uniform buffer objects
        model_ubo = device->create_buffer_memorys(sizeof(VulkanDeferredGPassModelData) * max_queued_jobs, 3);
        model_ubo_handles = pipeline.bind_uniform_buffer(device, model_ubo, 0);

        camera_ubo = device->create_buffer_memorys(sizeof(VulkanDeferredGPassCameraData), 3);
        camera_ubo_handles = pipeline.bind_uniform_buffer(device, camera_ubo, 1);

        material_ubo = device->create_buffer_memorys(sizeof(u32) * max_queued_jobs, 3);
        material_ubo_handles = pipeline.bind_uniform_buffer(device, material_ubo, 0);

        // Bind program
        set_program(program);
    }

    void VulkanDeferredGPass::record(ICommandEncoder* encoder) {
        auto vulkan_encoder = static_cast<VulkanCommandEncoder*>(encoder);

        auto cmd = vulkan_encoder->get_command_buffer();
        const auto& frame = vulkan_encoder->get_frame();

        // Upload frame specific data to GPU
        model_ubo[frame]->upload_data(
            vulkan_encoder->get_device(),
            queued_jobs_transform.data(),
            queued_jobs_transform.size() * sizeof(VulkanDeferredGPassModelData));

        auto aspect_ratio = static_cast<f32>(viewport.x) / static_cast<f32>(viewport.y);
        auto camera_data = VulkanDeferredGPassCameraData { .matrix = camera->calculate_matrix(aspect_ratio) };

        camera_ubo[frame]->upload_data(
            vulkan_encoder->get_device(),
            &camera_data,
            sizeof(VulkanDeferredGPassCameraData));

        // Record draw commands
        cmd->begin_render_pass(framebuffers[frame], render_pass);
            cmd->set_viewport(0, 0, viewport.x, viewport.y);
            program->bind(encoder);

            for(size_t i = 0; i < queued_jobs_model.size(); ++i) {
                const auto& model = queued_jobs_model[i];

                queued_jobs_handles[i].model_handle = model_ubo_handles[frame];
                queued_jobs_handles[i].model_instance = i;
                queued_jobs_handles[i].camera_handle = camera_ubo_handles[frame];

                auto vulkan_program = static_pointer_cast<VulkanProgram>(program);

                cmd->push_constant(
                    vulkan_program->get_pipeline().layout,
                    sizeof(VulkanDeferredGPassHandles),
                    0, &queued_jobs_handles[i]);

                auto mesh = model->get_mesh();

                mesh->bind(encoder);
                cmd->draw_indexed(mesh->triangle_count());
            }
        cmd->end_render_pass();
    }

    void VulkanDeferredGPass::reset() {
        queued_jobs_model.clear();
        queued_jobs_transform.clear();
    }

    void VulkanDeferredGPass::resize_viewport(const Vec2i& new_size) {
        // Todo
    }

    void VulkanDeferredGPass::submit_task(const std::shared_ptr<IModel>& mesh, const Transform& transform) {
        queued_jobs_model.push_back(mesh);
        queued_jobs_transform.push_back(calculate_transform_matrix(transform));
    }
}
