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

    class IAttachmentImpl : private core::NonCopyable {
        public:
            virtual ~IAttachmentImpl() = default;

            [[nodiscard]] virtual Vec2i get_size() const = 0;
            [[nodiscard]] virtual AttachmentType get_type() const = 0;
    };
}

#endif
