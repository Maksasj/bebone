#ifndef _BEBONE_CORE_ARENA_CONTAINER_H_
#define _BEBONE_CORE_ARENA_CONTAINER_H_

#include "arena_allocator.h"

namespace bebone::core {
    class ArenaContainer {
        private:
            ArenaAllocator data;
            ArenaAllocator indices;

        public:
            ArenaContainer(const size_t& size) : data(size), indices(size) {

            }

            ~ArenaContainer() {

            }

            ArenaContainer(const ArenaContainer&) = delete;
            void operator=(const ArenaContainer&) = delete;
            ArenaContainer &operator=(ArenaContainer&) = delete;

            void* alloc(const size_t& size) noexcept {
                void* ptr = data.alloc(size);
                void** indexPtr = static_cast<void**>(indices.alloc(sizeof(void*)));

                *indexPtr = ptr;

                return ptr;
            }

            void clear() noexcept {
                data.clear();
                indices.clear();
            }

            size_t size() const noexcept {
                return indices.allocated() / sizeof(void*);
            }

            size_t allocated() const noexcept {
                return data.allocated() + indices.allocated();
            }

            size_t capacity() const noexcept {
                return data.allocated() + indices.allocated();
            }

            void* at(const size_t& index) {
                void **data = static_cast<void**>(indices.data()); 
                return data[index];
            }
    };
}

#endif