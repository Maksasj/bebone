#include "ipresent_pass.h"

namespace bebone::renderer {
    IPresentPass::IPresentPass(
        const std::shared_ptr<IPassImpl>& impl,
        const std::string& pass_name,
        const Vec2i& viewport
    ) : IGraphicsPass(impl, pass_name, viewport) {
        register_resource("texture", texture_attachment);

        register_resource("render_target", render_target);
    }

    void IPresentPass::assemble(std::shared_ptr<IPassAssembler>& assember) {
        auto [ vert, frag ] = assember->get_shader_source("present_src");
        auto program = assember->create_program(get_impl(), vert, frag);
        set_program(program);

        quad_mesh = assember->get_default_quad();
    }

    void IPresentPass::record(ICommandEncoder* encoder) {
        encoder->begin_render_pass(render_target, get_impl());

        encoder->set_viewport(get_viewport());
        encoder->bind_program(program);

        encoder->bind_draw_data(program, texture_attachment);
        encoder->draw_indexed(quad_mesh);

        encoder->end_render_pass();
    }
}
