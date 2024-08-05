#include "iattachment.h"

namespace bebone::renderer {
    IAttachment::IAttachment(
        const std::shared_ptr<IAttachmentImpl>& impl,
        const std::string& name
    ) : impl(impl), name(name) {

    }

    const std::string& IAttachment::get_name() const {
        return name;
    }

    const std::shared_ptr<IAttachmentImpl>& IAttachment::get_impl() const {
        return impl;
    }
}
