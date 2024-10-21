#ifndef _BEBONE_RENDERER_ATTACHMENT_PLUG_H_
#define _BEBONE_RENDERER_ATTACHMENT_PLUG_H_

#include "iattachment.h"
#include "irender_target.h"

namespace bebone::renderer {
    class AttachmentPlug {
        private:
            std::string name;
            std::shared_ptr<IAttachment>& resource;
            bool pluged_flag;

        public:
            AttachmentPlug(const std::string& name, std::shared_ptr<IAttachment>& resource);

            void plug(const std::shared_ptr<IAttachment>& plug_attachment);

            const std::string& get_name() const;
            const bool& is_plugged() const;
    };

    class RenderTargetPlug {
        private:
            std::string name;
            std::shared_ptr<IRenderTarget>& resource;
            bool pluged_flag;

        public:
            RenderTargetPlug(const std::string& name, std::shared_ptr<IRenderTarget>& resource);

            void plug(const std::shared_ptr<IRenderTarget>& plug_attachment);

            const std::string& get_name() const;
            const bool& is_plugged() const;
    };
}

#endif
