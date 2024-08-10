#ifndef _BEBONE_RENDERER_IPASS_H_
#define _BEBONE_RENDERER_IPASS_H_

#include <string>

#include "renderer_backend.h"
#include "icommand_encoder.h"

#include "ipass_impl.h"
#include "iattachment.h"
#include "attachment_plug.h"
#include "ipass_assembler.h"

namespace bebone::renderer {
    using namespace bebone::core;

    class IPass : public NonCopyable {
        private:
            std::shared_ptr<IPassImpl> impl;

        private:
            std::string name;

            std::vector<AttachmentPlug> attachment_resources;
            std::vector<RenderTargetPlug> render_target_resources;

        protected:
            void register_resource(const std::string& name, std::shared_ptr<IAttachment>& attachment);
            void register_resource(const std::string& name, std::shared_ptr<IRenderTarget>& render_target);

        public:
            IPass(const std::shared_ptr<IPassImpl>& impl, std::string name);
            virtual ~IPass() = default;

            virtual void assemble(std::shared_ptr<IPassAssembler>& assember);
            virtual void check_requirements();
            virtual void record(ICommandEncoder* encoder);
            virtual void reset();

            virtual void resize_viewport(const Vec2i& new_size);

            void plug(const std::string& name, const std::shared_ptr<IAttachment>& attachment);
            void plug(const std::string& name, const std::shared_ptr<IRenderTarget>& render_target);

            [[nodiscard]] std::string get_name() const;

            void set_impl(const std::shared_ptr<IPassImpl>& new_impl);
            [[nodiscard]] std::shared_ptr<IPassImpl> get_impl() const;
    };
}

#endif
