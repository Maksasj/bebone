#ifndef _BEBONE_RENDERER_IATTACHMENT_FACTORY_H_
#define _BEBONE_RENDERER_IATTACHMENT_FACTORY_H_

#include <string>

#include "iattachment.h"

namespace bebone::renderer {
    using namespace bebone::gfx;

    class IAttachmentFactory {
        private:

        public:
            virtual ~IAttachmentFactory() = default;

            virtual std::shared_ptr<IAttachment> create_texture_attachment(const std::string& pass_name, const Vec2i& size) = 0;
            virtual std::shared_ptr<IAttachment> create_hdr_texture_attachment(const std::string& pass_name, const Vec2i& size) = 0;
            virtual std::shared_ptr<IAttachment> create_depth_attachment(const std::string& pass_name, const Vec2i& size) = 0;
    };
}

#endif
