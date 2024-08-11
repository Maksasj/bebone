#include "imesh.h"

namespace bebone::renderer {
    using namespace bebone::core;

    IMesh::IMesh(
        const std::shared_ptr<IMeshImpl>& impl
    ) : impl(impl) {

    }

    void IMesh::bind(ICommandEncoder* encoder) {
        impl->bind(encoder);
    }

    u64 IMesh::triangle_count() const {
        return impl->triangle_count();
    }

    u64 IMesh::vertex_count() const {
        return impl->vertex_count();
    }

    std::shared_ptr<IMeshImpl> IMesh::get_impl() const {
        return impl;
    }
}
