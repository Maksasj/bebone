#ifndef _BEBONE_RENDERER_IATTACHMENT_FACTORY_H_
#define _BEBONE_RENDERER_IATTACHMENT_FACTORY_H_

#include <string>

#include "iattachment.h"

#include "itexture_attachment.h"
#include "ihdr_texture_attachment.h"
#include "idepth_attachment.h"

namespace bebone::renderer {
    using namespace bebone::gfx;

    class IAttachmentFactory {
        private:

        public:
            virtual ~IAttachmentFactory() = default;

            virtual std::shared_ptr<ITextureAttachment> create_texture_attachment(const std::string& pass_name, const Vec2i& size) = 0;
            virtual std::shared_ptr<IHDRTextureAttachment> create_hdr_texture_attachment(const std::string& pass_name, const Vec2i& size) = 0;
            virtual std::shared_ptr<IDepthAttachment> create_depth_attachment(const std::string& pass_name, const Vec2i& size) = 0;
    };
}

#endif
