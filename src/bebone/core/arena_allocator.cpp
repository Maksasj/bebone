#include "arena_allocator.h"

namespace bebone::core {
    ArenaAllocator::ArenaAllocator(const size_t& size) : capacity(size), allocated(0) {
        data = malloc(size);
    }

    ArenaAllocator::ArenaAllocator(const size_t& size, void* buffer) : capacity(size), allocated(0) {
        data = buffer;
    }

    ArenaAllocator::~ArenaAllocator() {
        free(data);
    }

    void* ArenaAllocator::alloc(const size_t& size) noexcept {
        if(allocated + size > capacity) {
            return nullptr;
        }

        const size_t tmp_allocated = allocated;
        allocated += size;

        return static_cast<char*>(data) + tmp_allocated;
    }

    void* ArenaAllocator::get_data() noexcept {
        return data;
    }

    void ArenaAllocator::clear() noexcept {
        allocated = 0;
    }

    [[nodiscard]] const size_t& ArenaAllocator::get_allocated() const noexcept {
        return allocated;
    }

    [[nodiscard]] const size_t& ArenaAllocator::get_capacity() const noexcept {
        return capacity;
    }
}
