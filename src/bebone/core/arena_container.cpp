#include "arena_container.h"

namespace bebone::core {
    ArenaContainer::ArenaContainer(const size_t& size) : data(size), indices(size) {

    }

    void* ArenaContainer::alloc(const size_t& size) noexcept {
        void* ptr = data.alloc(size);
        void** indexPtr = static_cast<void**>(indices.alloc(sizeof(void*)));

        *indexPtr = ptr;

        return ptr;
    }

    void* ArenaContainer::at(const size_t& index) {
        void **ptr = static_cast<void**>(indices.data());
        return ptr[index];
    }

    void ArenaContainer::clear() noexcept {
        data.clear();
        indices.clear();
    }

    [[nodiscard]] size_t ArenaContainer::size() const noexcept {
        return indices.allocated() / sizeof(void*);
    }

    [[nodiscard]] size_t ArenaContainer::allocated() const noexcept {
        return data.allocated() + indices.allocated();
    }

    [[nodiscard]] size_t ArenaContainer::capacity() const noexcept {
        return data.allocated() + indices.allocated();
    }
}
