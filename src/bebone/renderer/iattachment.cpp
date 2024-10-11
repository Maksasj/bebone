#include "iattachment.h"

namespace bebone::renderer {
    IAttachment::IAttachment(
        const std::shared_ptr<IAttachmentImpl>& impl,
        const std::string& name
    ) : impl(impl), name(name) {

    }

    Vec2i IAttachment::get_size() const {
        return impl->get_size();
    }

    AttachmentType IAttachment::get_type() const {
        return impl->get_type();
    }

    const std::string& IAttachment::get_name() const {
        return name;
    }

    const std::shared_ptr<IAttachmentImpl>& IAttachment::get_impl() const {
        return impl;
    }
}
