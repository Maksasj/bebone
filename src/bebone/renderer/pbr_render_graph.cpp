#include "pbr_render_graph.h"

namespace bebone::renderer {
    using namespace bebone::gfx;

    PBRRenderGraph::PBRRenderGraph(const std::string& name, const std::shared_ptr<IRenderGraphImpl>& impl) : IRenderGraph(name, impl) {
        auto size = Vec2i(800, 600);

        auto pass_factory = create_pass_factory();
        auto resource_factory = create_resource_factory();

        auto gpass_position_texture = resource_factory->create_texture_resource("gpass_position_texture", size);
        add_resource(gpass_position_texture);

        auto gpass_normals_texture = resource_factory->create_texture_resource("gpass_normals_texture", size);
        add_resource(gpass_normals_texture);

        auto gpass_albedo_texture = resource_factory->create_texture_resource("gpass_albedo_texture", size);
        add_resource(gpass_albedo_texture);

        auto gpass_specular_texture = resource_factory->create_texture_resource("gpass_specular_texture", size);
        add_resource(gpass_specular_texture);

        auto gpass_depth = resource_factory->create_depth_resource("gpass_depth", size);
        add_resource(gpass_depth);

        gpass = pass_factory->create_deferred_g_pass("gpass", size);
        gpass->plug_output("position", gpass_position_texture);
        gpass->plug_output("normals", gpass_normals_texture);
        gpass->plug_output("albedo", gpass_albedo_texture);
        gpass->plug_output("specular", gpass_specular_texture);

        gpass->plug_output("depth", gpass_depth);
        add_pass(gpass);

        present = pass_factory->create_present_pass("present", size);
        present->plug_input("texture", gpass_albedo_texture);
        add_pass(present);
    }

    void PBRRenderGraph::submit_geometry(const std::shared_ptr<IMesh>& mesh, const Transform& transform) {
        gpass->submit_task(mesh, transform);
    }

    void PBRRenderGraph::submit_ui_geometry(const std::shared_ptr<IMesh>& mesh, const Transform& transform) {
        std::ignore = mesh;
        std::ignore = transform;
    }
}
