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

    "layout(set = 0, binding = 0) uniform CameraUBO {\n"
    "   mat4 matrix;\n"
    "} cameraUBO [];\n"

    "layout( push_constant ) uniform Handles {\n"
    "    mat4 transform;\n"
    "    int camera_handle;\n"
    "} handles;\n"

    "void main() {\n"
    "    mat4 model = handles.transform;\n"
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

    "layout(set = 0, binding = 0) uniform MaterialUBO {\n"
    "   int albedo_handle;\n"
    "   int height_handle;\n"
    "   int metallic_handle;\n"
    "   int roughness_handle;\n"
    "} materialUBO [];\n"

    "layout(std140, push_constant) uniform Handles {\n"
    "    mat4 transform;\n"
    "    int camera_handle;\n"
    "    int material_handle;\n"
    "} handles;\n"

    "layout(set = 0, binding = 2) uniform sampler2D textures[];\n"

    "void main() {\n"
    "   out_position = vec4(in_position, 1.0);\n"
    "   out_normals = vec4((in_normal + vec3(1.0f, 1.0f, 1.0f)) / 2.0f, 1.0);\n"
    "   out_albedo =  vec4(texture(textures[materialUBO[handles.material_handle].albedo_handle], in_texcoord));\n"
    "   out_specular = vec4(texture(textures[materialUBO[handles.material_handle].roughness_handle], in_texcoord));\n"
    "}";

namespace bebone::renderer {
    using namespace bebone::gfx;

    // Present pass
    VulkanDeferredGPass::VulkanDeferredGPass(
        const std::shared_ptr<IPassImpl>& impl,
        const std::string& pass_name,
        const Vec2i& viewport
    ) : IDeferredGPass(impl, pass_name, viewport) {
        queued_jobs.reserve(max_queued_jobs);
    }

    void VulkanDeferredGPass::assemble(IPassAssembler* assember) {
        auto program = assember->get_program_manager()->create_program(
            get_impl(),
            vulkan_deferred_g_pass_vertex_shader_code,
            vulkan_deferred_g_pass_fragment_shader_code);

        set_program(program);

        // Setup render target
        auto vulkan_assembler = static_cast<VulkanPassAssembler*>(assember);
        auto device = vulkan_assembler->get_device();
        auto texture_manager = vulkan_assembler->get_texture_manager();

        target = assember->create_render_target({
            position_attachment,
            normals_attachment,
            albedo_attachment,
            specular_attachment,
            depth_attachment
        }, get_viewport());

        target = std::make_shared<VulkanRendererTarget>(vector {
            position_attachment,
            normals_attachment,
            albedo_attachment,
            specular_attachment,
            depth_attachment
        }, get_viewport());

        // Camera data Todo fix camera thing
        // camera_ubo = device->create_buffer_memorys(sizeof(VulkanDeferredGPassCameraData), 3);
        // camera_ubo_handles  = pipeline_manager->bind_uniform_buffers(device, camera_ubo);
    }

    void VulkanDeferredGPass::record(ICommandEncoder* encoder) {
        // Update camera data
        auto camera_data = VulkanDeferredGPassCameraData {
            .matrix = camera->calculate_matrix(get_viewport_aspect_ratio())
        };

        auto vulkan_encoder = static_cast<VulkanCommandEncoder*>(encoder);
        const auto& frame = vulkan_encoder->get_frame();
        camera_ubo[frame]->upload_data(
            vulkan_encoder->get_device(),
            &camera_data,
            sizeof(VulkanDeferredGPassCameraData));

        // Record draw commands
        // cmd->begin_render_pass(framebuffers[frame], render_pass);

        encoder->begin_render_pass(target, get_impl());

        encoder->set_viewport(get_viewport());
        encoder->bind_program(program);

        for(const auto& [ mesh, material, transform ] : queued_jobs) {
            const auto handles = VulkanDeferredGPassHandles {
               .transform = calculate_transform_matrix(transform),
               .camera_handle = camera_ubo_handles[frame],
               .material_handle = static_cast<VulkanBindlessBufferHandle>(material)
            };

            auto cmd = vulkan_encoder->get_command_buffer();
            cmd->push_constant(pipeline_layout, sizeof(VulkanDeferredGPassHandles), 0, &handles);

            // mesh_manager->draw_indexed(encoder, mesh);

            encoder->draw_indexed(mesh);
        }

        encoder->end_render_pass();

        // cmd->end_render_pass();
    }

    void VulkanDeferredGPass::reset() {
        queued_jobs.clear();
    }

    void VulkanDeferredGPass::resize_viewport(const Vec2i& new_size) {
        // Todo
    }

    void VulkanDeferredGPass::submit_task(const RenderQueueTask& task) {
        queued_jobs.push_back(task);
    }
}
