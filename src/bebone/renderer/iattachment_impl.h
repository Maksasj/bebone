#ifndef _BEBONE_RENDERER_IATTACHMENT_IMPL_H_
#define _BEBONE_RENDERER_IATTACHMENT_IMPL_H_

#include "renderer_backend.h"
#include "itexture_impl.h"

namespace bebone::renderer {

    enum AttachmentType {
        Color,
        HDRColor,
        Depth
    };

    class IAttachmentImpl : public core::NonCopyable {
        private:

        public:

    };
}

#endif
