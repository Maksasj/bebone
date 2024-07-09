#include "iresource.h"

namespace bebone::renderer {
    IResource::IResource(const std::string& name) : name(name) {

    }

    const std::string& IResource::get_name() const {
        return name;
    }
}
