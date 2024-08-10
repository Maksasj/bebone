#include "ideferred_g_pass.h"

static const char deferred_g_pass_vert_src[] =
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

static const char deferred_g_pass_frag_src[] =
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
    using namespace bebone::core;

    IDeferredGPass::IDeferredGPass(
        const std::shared_ptr<IPassImpl>& impl,
        const std::string& pass_name,
        const Vec2i& viewport
    ) : IRenderQueuePass(impl, pass_name, viewport) {
        register_resource("render_target", render_target);
    }

    void IDeferredGPass::assemble(std::shared_ptr<IPassAssembler>& assember) {
        auto program = assember->create_program(get_impl(), deferred_g_pass_vert_src, deferred_g_pass_frag_src);
        set_program(program);

        camera_ubo = assember->create_uniform_buffer(sizeof(Mat4f));
    }

    void IDeferredGPass::record(ICommandEncoder* encoder) {
        auto camera_data = camera->calculate_matrix(get_viewport_aspect_ratio());
        camera_ubo->upload_data(&camera_data, sizeof(Mat4f));

        encoder->begin_render_pass(render_target, get_impl());

        encoder->set_viewport(get_viewport());
        encoder->bind_program(program);

        for(const auto& [ mesh, material, transform ] : queued_jobs) {
            encoder->bind_draw_data(program, transform, camera_ubo, material);
            encoder->draw_indexed(mesh);
        }

        encoder->end_render_pass();
    }
}
