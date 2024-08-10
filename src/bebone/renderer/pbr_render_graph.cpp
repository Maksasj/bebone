#include "pbr_render_graph.h"

namespace bebone::renderer {
    using namespace bebone::gfx;

    PBRRenderGraph::PBRRenderGraph(
        const std::shared_ptr<IRenderGraphImpl>& impl,
        const std::string& name,
        const Vec2i& viewport
    ) : IRenderGraph(impl, name) {
        // Attachments
        auto attachment_factory = create_attachment_factory();
        auto gpass_position = attachment_factory->create_hdr_texture_attachment("gpass_position_texture", viewport);
        auto gpass_normals = attachment_factory->create_hdr_texture_attachment("gpass_normals_texture", viewport);
        auto gpass_albedo = attachment_factory->create_hdr_texture_attachment("gpass_albedo_texture", viewport);
        auto gpass_specular = attachment_factory->create_hdr_texture_attachment("gpass_specular_texture", viewport);
        auto gpass_depth = attachment_factory->create_depth_attachment("gpass_depth", viewport);

        add_attachment(gpass_position);
        add_attachment(gpass_normals);
        add_attachment(gpass_albedo);
        add_attachment(gpass_specular);
        add_attachment(gpass_depth);

        // Passes
        auto pass_factory = create_pass_factory();

        gpass = std::make_shared<IDeferredGPass>(pass_factory->create_deferred_g_pass_impl(viewport), "gpass", viewport);
        add_pass(gpass);

        present = std::make_shared<IPresentPass>(pass_factory->create_present_pass_impl(), "present", viewport);
        present->plug("texture", gpass_normals);
        add_pass(present);

        // Render targets
        auto assembler = create_pass_assembler();

        auto deferred_target = std::make_shared<IRenderTarget>(assembler->create_render_target_impl(gpass->get_impl(), {
            gpass_position, gpass_normals, gpass_albedo, gpass_specular, gpass_depth
        }, viewport), "deferred_target");
        gpass->plug("render_target", deferred_target);
        add_target(deferred_target);

        auto present_target = std::make_shared<IRenderTarget>(assembler->create_present_target_impl(), "present_target");
        present->plug("render_target", present_target);
        add_target(present_target);
    }

    void PBRRenderGraph::submit_geometry_task(const MeshHandle& mesh, const MaterialHandle& material, const Transform& transform) {
        gpass->submit_task({ mesh, material, transform });
    }

    void PBRRenderGraph::submit_ui_geometry_task(const MeshHandle& mesh, const MaterialHandle& material, const Transform& transform) {
        // Todo

        std::ignore = mesh;
        std::ignore = material;
        std::ignore = transform;
    }
}
