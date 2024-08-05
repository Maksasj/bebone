#include "vulkan_present_pass.h"

static const char vulkan_present_pass_vertex_shader_code[] =
    "#version 450 core\n"
    "#extension GL_EXT_nonuniform_qualifier : enable\n"

    "layout (location = 0) in vec3 position;\n"
    "layout (location = 1) in vec3 normal;\n"
    "layout (location = 2) in vec2 texcoord;\n"

    "layout (location = 0) out vec3 out_normal;\n"
    "layout (location = 1) out vec2 out_texcoord;\n"

    "void main() {\n"
    "    gl_Position = vec4(position, 1.0);\n"

    "    out_normal = normal;\n"
    "    out_texcoord = texcoord;\n"
    "}";

static const char vulkan_present_pass_fragment_shader_code[] =
    "#version 450 core\n"
    "#extension GL_EXT_nonuniform_qualifier : enable\n"

    "layout (location = 0) in vec3 normal;\n"
    "layout (location = 1) in vec2 texcoord;\n"

    "layout (location = 0) out vec4 out_color;\n"

    "layout(set = 0, binding = 2) uniform sampler2D textures[];\n"

    "layout( push_constant ) uniform Handles {\n"
    "    int texture;\n"
    "} handles;\n"

    "void main() {\n"
    "   out_color = texture(textures[handles.texture], texcoord);\n"
    "}";

namespace bebone::renderer {
    using namespace bebone::gfx;

    // Present pass
    VulkanPresentPass::VulkanPresentPass(
        const std::shared_ptr<IPassImpl>& impl,
        const std::string& pass_name,
        const Vec2i& viewport
    ) : IPresentPass(impl, pass_name, viewport) {

    }

    void VulkanPresentPass::assemble(IPassAssembler* assember) {
        auto vulkan_assembler = static_cast<VulkanPassAssembler*>(assember);
        mesh_manager = vulkan_assembler->get_mesh_manager();

        // Todo
        auto program = assember->get_program_manager()->create_program(
            get_impl(),
            vulkan_present_pass_vertex_shader_code,
            vulkan_present_pass_fragment_shader_code);

        set_program(program);

        // Todo, move this to mesh manager
        quad_mesh = mesh_manager->generate_mesh(std::make_shared<QuadMeshGenerator>(1.0f, 1.0f, Vec3f::back));
    }

    void VulkanPresentPass::record(ICommandEncoder* encoder) {
        auto vulkan_encoder = static_cast<VulkanCommandEncoder*>(encoder);

        // cmd->begin_render_pass(vulkan_encoder->get_swap_chain());

        encoder->begin_render_pass(target, get_impl());

        encoder->set_viewport(get_viewport());
        encoder->bind_program(program);

        const auto texture = static_pointer_cast<VulkanHDRTextureAttachment>(texture_attachment);
        const auto& frame = vulkan_encoder->get_frame();
        auto handles = u32(texture->get_handles()[frame]);

        auto cmd = vulkan_encoder->get_command_buffer();
        cmd->push_constant(pipeline_layout, sizeof(u32), 0, &handles);
        mesh_manager->draw_indexed(encoder, quad_mesh);

        encoder->end_render_pass();

        // cmd->end_render_pass();
    }

    void VulkanPresentPass::reset() {

    }

    void VulkanPresentPass::resize_viewport(const Vec2i& new_size) {
        // Todo
    }
}
