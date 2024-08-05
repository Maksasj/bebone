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

            std::vector<AttachmentPlug> inputs;
            std::vector<AttachmentPlug> outputs;

        protected:
            void register_input(const std::string& attachment_name, std::shared_ptr<IAttachment>& attachment);
            void register_output(const std::string& attachment_name, std::shared_ptr<IAttachment>& attachment);

        public:
            IPass(const std::shared_ptr<IPassImpl>& impl, std::string name);
            virtual ~IPass() = default;

            virtual void assemble(IPassAssembler* assember) = 0;
            virtual void check_requirements() = 0;
            virtual void record(ICommandEncoder* encoder) = 0;
            virtual void reset() = 0;

            virtual void resize_viewport(const Vec2i& new_size) = 0;

            void plug_input(const std::string& attachment_name, const std::shared_ptr<IAttachment>& attachment);
            void plug_output(const std::string& attachment_name, const std::shared_ptr<IAttachment>& attachment);

            [[nodiscard]] std::string get_name() const;
            [[nodiscard]] std::shared_ptr<IPassImpl> get_impl() const;
    };
}

#endif
