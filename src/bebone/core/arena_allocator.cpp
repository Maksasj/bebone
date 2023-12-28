#include "arena_allocator.h"

namespace bebone::core {
    ArenaAllocator::ArenaAllocator(const size_t& size) : _capacity(size), _allocated(0) {
        _data = malloc(size);
    }

    ArenaAllocator::ArenaAllocator(const size_t& size, void* buffer) : _capacity(size), _allocated(0) {
        _data = buffer;
    }

    ArenaAllocator::~ArenaAllocator() {
        free(_data);
    }

    void* ArenaAllocator::alloc(const size_t& size) noexcept {
        if(_allocated + size > _capacity) {
            return nullptr;
        }

        const size_t allocated = _allocated;
        _allocated += size;

        return static_cast<char*>(_data) + allocated;
    }

    void* ArenaAllocator::data() noexcept {
        return _data;
    }

    void ArenaAllocator::clear() noexcept {
        _allocated = 0;
    }

    [[nodiscard]] const size_t& ArenaAllocator::allocated() const noexcept {
        return _allocated;
    }

    [[nodiscard]] const size_t& ArenaAllocator::capacity() const noexcept {
        return _capacity;
    }
}
