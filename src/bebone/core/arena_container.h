#ifndef _BEBONE_CORE_ARENA_CONTAINER_H_
#define _BEBONE_CORE_ARENA_CONTAINER_H_

#include "noncopyable.h"
#include "arena_allocator.h"

namespace bebone::core {
    class ArenaContainer : private core::NonCopyable {
        private:
            ArenaAllocator data;
            ArenaAllocator indices;

        public:
            explicit ArenaContainer(const size_t& size);

            void* alloc(const size_t& size) noexcept;
            void* at(const size_t& index);

            void clear() noexcept;

            [[nodiscard]] size_t size() const noexcept;
            [[nodiscard]] size_t allocated() const noexcept;
            [[nodiscard]] size_t capacity() const noexcept;
    };
}

#endif