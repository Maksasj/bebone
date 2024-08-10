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
            std::shared_ptr<IRenderGraphImpl> impl;
            std::string name;

        public:
            IRenderGraph(const std::shared_ptr<IRenderGraphImpl>& impl, std::string name);
            virtual ~IRenderGraph() = default;

            virtual void assemble();
            virtual void record();
            virtual void submit();
            virtual void reset();

            virtual void resize_viewport(const Vec2i& new_size);

            // Helper functions
            virtual void submit_geometry_task(const MeshHandle& mesh, const MaterialHandle& material, const Transform& transform);
            virtual void submit_ui_geometry_task(const MeshHandle& mesh, const MaterialHandle& material, const Transform& transform);

            virtual std::shared_ptr<IPassAssembler> create_pass_assembler() const;
            [[nodiscard]] virtual std::shared_ptr<IPassImplFactory> create_pass_factory() const;
            [[nodiscard]] virtual std::shared_ptr<IAttachmentFactory> create_attachment_factory() const;

            void add_pass(const std::shared_ptr<IPass>& render_pass);
            [[nodiscard]] std::optional<std::shared_ptr<IPass>> get_render_pass(const std::string& name) const;
            [[nodiscard]] std::vector<std::shared_ptr<IPass>>& get_render_passes();

            void add_attachment(const std::shared_ptr<IAttachment>& render_attachment);
            [[nodiscard]] std::optional<std::shared_ptr<IAttachment>> get_render_attachment(const std::string& name) const;
            [[nodiscard]] std::vector<std::shared_ptr<IAttachment>>& get_render_attachments();

            void add_target(const std::shared_ptr<IRenderTarget>& render_target);
            [[nodiscard]] std::optional<std::shared_ptr<IRenderTarget>> get_render_target(const std::string& name) const;
            [[nodiscard]] std::vector<std::shared_ptr<IRenderTarget>>& get_render_targets();
    };
}

#endif
