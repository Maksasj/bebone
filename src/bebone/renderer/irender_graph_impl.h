#ifndef _BEBONE_RENDERER_IRENDER_GRAPH_IMPL_H_
#define _BEBONE_RENDERER_IRENDER_GRAPH_IMPL_H_

#include "renderer_backend.h"

#include "ipass.h"
#include "ipass_factory.h"
#include "iattachment_factory.h"
#include "idebug_camera.h"

namespace bebone::renderer {
    class IRenderGraphImpl {
        private:
            std::vector<std::shared_ptr<IPass>> render_passes;
            std::vector<std::shared_ptr<IAttachment>> render_resources;
            std::vector<std::shared_ptr<IRenderTarget>> render_targets;

        public:
            virtual ~IRenderGraphImpl() = default;

            virtual void assemble() = 0;
            virtual void record() = 0;
            virtual void submit() = 0;
            virtual void reset() = 0;

            virtual void resize_viewport(const Vec2i& new_size) = 0;

            virtual std::shared_ptr<IPassAssembler> create_pass_assembler() const = 0;
            virtual std::shared_ptr<IPassImplFactory> create_pass_factory() const = 0;
            virtual std::shared_ptr<IAttachmentFactory> create_attachment_factory() const = 0;

            void add_pass(const std::shared_ptr<IPass>& render_pass);
            [[nodiscard]] std::optional<std::shared_ptr<IPass>> get_render_pass(const std::string& name) const;
            std::vector<std::shared_ptr<IPass>>& get_render_passes();

            void add_attachment(const std::shared_ptr<IAttachment>& render_attachment);
            [[nodiscard]] std::optional<std::shared_ptr<IAttachment>> get_render_attachment(const std::string& name) const;
            std::vector<std::shared_ptr<IAttachment>>& get_render_attachments();

            void add_target(const std::shared_ptr<IRenderTarget>& render_target);
            [[nodiscard]] std::optional<std::shared_ptr<IRenderTarget>> get_render_target(const std::string& name) const;
            std::vector<std::shared_ptr<IRenderTarget>>& get_render_targets();
    };
}

#endif
