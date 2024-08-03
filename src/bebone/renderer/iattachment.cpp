#include "iattachment.h"

namespace bebone::renderer {
    IAttachment::IAttachment(const std::string& name) : name(name) {

    }

    const std::string& IAttachment::get_name() const {
        return name;
    }
}
