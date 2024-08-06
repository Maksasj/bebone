#ifndef _BEBONE_RENDERER_IRENDER_GRAPH_H_
#define _BEBONE_RENDERER_IRENDER_GRAPH_H_

#include "iperspective_camera.h"
#include "irender_graph_impl.h"

namespace bebone::renderer {
    class IRenderer;
    class GLRenderer;
    class VulkanRenderer;

    class IRenderGraph : public NonCopyable {
        private:
            std::string name;
            std::shared_ptr<IRenderGraphImpl> impl;

        public:
            IRenderGraph(const std::string& name, const std::shared_ptr<IRenderGraphImpl>& impl);
            virtual ~IRenderGraph() = default;

            virtual void assemble();
            virtual void record();
            virtual void submit();
            virtual void reset();

            virtual void resize_viewport(const Vec2i& new_size);

            // Helper functions
            virtual void submit_geometry_task(const MeshHandle& mesh, const MaterialHandle& material, const Transform& transform);
            virtual void submit_ui_geometry_task(const MeshHandle& mesh, const MaterialHandle& material, const Transform& transform);

            virtual std::shared_ptr<IPassImplFactory> create_pass_factory() const;
            virtual std::shared_ptr<IAttachmentFactory> create_attachment_factory() const;

            void add_pass(const std::shared_ptr<IPass>& render_pass);
            std::optional<std::shared_ptr<IPass>> get_render_pass(const std::string& pass_name) const;
            std::vector<std::shared_ptr<IPass>>& get_render_passes();

            void add_attachment(const std::shared_ptr<IAttachment>& render_attachment);
            std::optional<std::shared_ptr<IAttachment>> get_render_attachment(const std::string& attachment_name) const;
            std::vector<std::shared_ptr<IAttachment>>& get_render_attachments();
    };
}

#endif
