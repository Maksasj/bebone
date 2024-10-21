#ifndef _BEBONE_RENDERER_IATTACHMENT_H_
#define _BEBONE_RENDERER_IATTACHMENT_H_

#include <string>

#include "renderer_backend.h"
#include "iattachment_impl.h"

namespace bebone::renderer {
    class IAttachment : private NonCopyable {
        private:
            std::shared_ptr<IAttachmentImpl> impl;
            std::string name;

        public:
            IAttachment(const std::shared_ptr<IAttachmentImpl>& impl, const std::string& name);
            virtual ~IAttachment() = default;

            [[nodiscard]] Vec2i get_size() const;
            [[nodiscard]] AttachmentType get_type() const;
            [[nodiscard]] const std::string& get_name() const;
            [[nodiscard]] const std::shared_ptr<IAttachmentImpl>& get_impl() const;
    };
}

#endif
