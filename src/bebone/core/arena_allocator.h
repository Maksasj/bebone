#ifndef _BEBONE_CORE_ARENA_ALLOCATOR_H_
#define _BEBONE_CORE_ARENA_ALLOCATOR_H_

#include <memory>

#define _BEBONE_MEMORY_BYTES_1KB_ 1024
#define _BEBONE_MEMORY_BYTES_2KB_ 2048
#define _BEBONE_MEMORY_BYTES_4KB_ 4096
#define _BEBONE_MEMORY_BYTES_8KB_ 8192

namespace bebone::core {
    class ArenaAllocator {
        private:
            void *_data;
            const size_t _capacity;
            size_t _allocated;

        public:
            ArenaAllocator(const size_t& size) : _capacity(size), _allocated(0) {
                _data = malloc(size);
            }

            ArenaAllocator(const size_t& size, void* buffer) : _capacity(size), _allocated(0) {
                _data = buffer;
            }

            ~ArenaAllocator() {
                free(_data);
            }

            ArenaAllocator(const ArenaAllocator&) = delete;
            void operator=(const ArenaAllocator&) = delete;
            ArenaAllocator &operator=(ArenaAllocator&) = delete;

            void* alloc(const size_t& size) noexcept {
                if(_allocated + size > _capacity) {
                    return nullptr;
                }

                _allocated += size;

                return static_cast<char*>(_data) + _allocated;
            }

            void clear() noexcept {
                _allocated = 0;
            }

            size_t allocated() const noexcept {
                return _allocated;
            }

            size_t capacity() const noexcept {
                return _capacity;
            }
    };
}

#endif