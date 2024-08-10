#include "pbr_render_graph.h"

namespace bebone::renderer {
    using namespace bebone::gfx;

    PBRRenderGraph::PBRRenderGraph(const std::string& name, const Vec2i& viewport, const std::shared_ptr<IRenderGraphImpl>& impl) : IRenderGraph(name, impl) {
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
        gpass->plug("position", gpass_position);
        gpass->plug("normals", gpass_normals);
        gpass->plug("albedo", gpass_albedo);
        gpass->plug("specular", gpass_specular);
        gpass->plug("depth", gpass_depth);

        present = std::make_shared<IPresentPass>(pass_factory->create_present_pass_impl(), "present", viewport);
        present->plug("texture", gpass_normals);

        add_pass(gpass);
        add_pass(present);
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
