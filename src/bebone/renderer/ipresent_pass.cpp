#include "ipresent_pass.h"

static const char present_vert_src[] =
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

static const char present_frag_src[] =
    "#version 450 core\n"
    "#extension GL_EXT_nonuniform_qualifier : enable\n"

    "layout (location = 0) in vec3 normal;\n"
    "layout (location = 1) in vec2 texcoord;\n"

    "layout (location = 0) out vec4 out_color;\n"

    "layout(set = 0, binding = 2) uniform sampler2D textures[];\n"

    "layout(std140, push_constant) uniform Handles {\n"
    "    int texture;\n"
    "} handles;\n"

    "void main() {\n"
    "   out_color = texture(textures[handles.texture], texcoord);\n"
    "}";

namespace bebone::renderer {
    IPresentPass::IPresentPass(
        const std::shared_ptr<IPassImpl>& impl,
        const std::string& pass_name,
        const Vec2i& viewport
    ) : IGraphicsPass(impl, pass_name, viewport) {
        register_resource("texture", texture_attachment);
    }

    void IPresentPass::assemble(IPassAssembler* assember) {
        target = assember->create_present_target("present_target");

        auto program = assember->get_program_manager()->create_program(get_impl(), present_vert_src, present_frag_src);
        set_program(program);

        quad_mesh = assember->get_mesh_manager()->get_default_quad();
    }

    void IPresentPass::record(ICommandEncoder* encoder) {
        encoder->begin_render_pass(target, get_impl());

        encoder->set_viewport(get_viewport());
        encoder->bind_program(program);

        encoder->bind_draw_data(program, texture_attachment);
        encoder->draw_indexed(quad_mesh);

        encoder->end_render_pass();
    }

    void IPresentPass::reset() {

    }

    void IPresentPass::resize_viewport(const Vec2i& new_size) {
        // Todo
    }
}
