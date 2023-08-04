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
            ArenaAllocator(size_t size) : _capacity(size), _allocated(0) {
                _data = malloc(size);
            }

            ~ArenaAllocator() {
                free(_data);
            }

            ArenaAllocator(const ArenaAllocator&) = delete;
            void operator=(const ArenaAllocator&) = delete;
            ArenaAllocator(ArenaAllocator&&) = delete;
            ArenaAllocator &operator=(ArenaAllocator&) = delete;

            void* alloc(size_t size) {
                if(_allocated + size > _capacity) {
                    return nullptr;
                }

                _allocated += size;

                return static_cast<char*>(_data) + _allocated;
            }

            void clear() {
                _allocated = 0;
            }
    };
}

#endif