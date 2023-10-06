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
            explicit ArenaAllocator(const size_t& size) : _capacity(size), _allocated(0) {
                _data = malloc(size);
            }

            explicit ArenaAllocator(const size_t& size, void* buffer) : _capacity(size), _allocated(0) {
                _data = buffer;
            }

            ~ArenaAllocator() {
                free(_data);
            }

            void* alloc(const size_t& size) noexcept {
                if(_allocated + size > _capacity) {
                    return nullptr;
                }

                const size_t allocated = _allocated;
                _allocated += size;

                return static_cast<char*>(_data) + allocated;
            }

            void clear() noexcept {
                _allocated = 0;
            }

            [[nodiscard]] const size_t& allocated() const noexcept {
                return _allocated;
            }

            [[nodiscard]] const size_t& capacity() const noexcept {
                return _capacity;
            }

            void* data() noexcept {
                return _data;
            }
    };
}

#endif