#include "pbr_render_graph.h"

namespace bebone::renderer {
    using namespace bebone::gfx;

    PBRRenderGraph::PBRRenderGraph(const std::string& name, const Vec2i& viewport, const std::shared_ptr<IRenderGraphImpl>& impl) : IRenderGraph(name, impl) {
        auto pass_factory = create_pass_factory();
        auto attachment_factory = create_attachment_factory();

        auto gpass_position_texture = attachment_factory->create_hdr_texture_attachment("gpass_position_texture", viewport);
        add_attachment(gpass_position_texture);

        auto gpass_normals_texture = attachment_factory->create_hdr_texture_attachment("gpass_normals_texture", viewport);
        add_attachment(gpass_normals_texture);

        auto gpass_albedo_texture = attachment_factory->create_hdr_texture_attachment("gpass_albedo_texture", viewport);
        add_attachment(gpass_albedo_texture);

        auto gpass_specular_texture = attachment_factory->create_hdr_texture_attachment("gpass_specular_texture", viewport);
        add_attachment(gpass_specular_texture);

        auto gpass_depth = attachment_factory->create_depth_attachment("gpass_depth", viewport);
        add_attachment(gpass_depth);

        gpass = std::make_shared<IDeferredGPass>(pass_factory->create_deferred_g_pass_impl(viewport), "gpass", viewport);
        gpass->plug_output("position", gpass_position_texture);
        gpass->plug_output("normals", gpass_normals_texture);
        gpass->plug_output("albedo", gpass_albedo_texture);
        gpass->plug_output("specular", gpass_specular_texture);

        gpass->plug_output("depth", gpass_depth);
        add_pass(gpass);

        present = std::make_shared<IPresentPass>(pass_factory->create_present_pass_impl(), "present", viewport);
        present->plug_input("texture", gpass_normals_texture);
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
