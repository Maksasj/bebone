#include "ideferred_g_pass.h"

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
        auto [ vert, frag ] = assember->get_shader_source("deferred_g_src");
        auto program = assember->create_program(get_impl(), vert, frag);
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
