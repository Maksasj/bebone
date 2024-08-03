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
            std::vector<std::shared_ptr<IAttachment>> render_attachments;

        public:
            IRenderGraphImpl();
            virtual ~IRenderGraphImpl() = default;

            virtual void assemble() = 0;
            virtual void record() = 0;
            virtual void submit() = 0;
            virtual void reset() = 0;

            virtual void resize_viewport(const Vec2i& new_size) = 0;

            virtual std::shared_ptr<IPassFactory> create_pass_factory() const = 0;
            virtual std::shared_ptr<IAttachmentFactory> create_attachment_factory() const = 0;

            void add_pass(const std::shared_ptr<IPass>& render_pass);
            std::optional<std::shared_ptr<IPass>> get_render_pass(const std::string& pass_name) const;
            std::vector<std::shared_ptr<IPass>>& get_render_passes();

            void add_attachment(const std::shared_ptr<IAttachment>& render_attachment);
            std::optional<std::shared_ptr<IAttachment>> get_render_attachment(const std::string& attachment_name) const;
            std::vector<std::shared_ptr<IAttachment>>& get_render_attachments();
    };
}

#endif
