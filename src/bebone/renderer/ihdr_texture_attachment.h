#ifndef _BEBONE_RENDERER_IHDR_TEXTURE_ATTACHMENT_H_
#define _BEBONE_RENDERER_IHDR_TEXTURE_ATTACHMENT_H_

#include "iattachment.h"

namespace bebone::renderer {
    class IHDRTextureAttachment : public IAttachment {
        private:

        public:
            IHDRTextureAttachment(const std::string& name);
    };
}

#endif
