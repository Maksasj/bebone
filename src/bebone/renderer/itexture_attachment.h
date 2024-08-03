#ifndef _BEBONE_RENDERER_ITEXTURE_ATTACHMENT_H_
#define _BEBONE_RENDERER_ITEXTURE_ATTACHMENT_H_

#include "iattachment.h"

namespace bebone::renderer {
    class ITextureAttachment : public IAttachment {
        private:

        public:
            ITextureAttachment(const std::string& name);
    };
}

#endif
