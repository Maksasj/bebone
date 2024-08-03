#ifndef _BEBONE_RENDERER_ATTACHMENT_PLUG_H_
#define _BEBONE_RENDERER_ATTACHMENT_PLUG_H_

#include "iattachment.h"

namespace bebone::renderer {
    class AttachmentPlug {
        private:
            std::string name;
            std::shared_ptr<IAttachment>& attachment;
            bool pluged_flag;

        public:
            AttachmentPlug(const std::string& name, std::shared_ptr<IAttachment>& attachment);

            void plug(const std::shared_ptr<IAttachment>& plug_attachment);

            const std::string& get_name() const;
            const bool& is_plugged() const;
    };
}

#endif
