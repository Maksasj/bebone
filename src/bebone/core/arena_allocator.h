#ifndef _BEBONE_CORE_ARENA_ALLOCATOR_H_
#define _BEBONE_CORE_ARENA_ALLOCATOR_H_

#include <memory>

#include "noncopyable.h"

#define _BEBONE_MEMORY_BYTES_1KB_ 1024
#define _BEBONE_MEMORY_BYTES_2KB_ 2048
#define _BEBONE_MEMORY_BYTES_4KB_ 4096
#define _BEBONE_MEMORY_BYTES_8KB_ 8192

namespace bebone::core {
    class ArenaAllocator : private core::NonCopyable {
        private:
            void *_data;
            const size_t _capacity;
            size_t _allocated;

        public:
            explicit ArenaAllocator(const size_t& size);
            explicit ArenaAllocator(const size_t& size, void* buffer);

            ~ArenaAllocator();

            void* alloc(const size_t& size) noexcept;
            void* data() noexcept;

            void clear() noexcept;

            [[nodiscard]] const size_t& allocated() const noexcept;
            [[nodiscard]] const size_t& capacity() const noexcept;
    };
}

#endif