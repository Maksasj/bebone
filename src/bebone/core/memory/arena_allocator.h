#ifndef _BEBONE_CORE_ARENA_ALLOCATOR_H_
#define _BEBONE_CORE_ARENA_ALLOCATOR_H_

#include <memory>

#include "noncopyable.h"

#define _BEBONE_MEMORY_BYTES_1KB_ 1024
#define _BEBONE_MEMORY_BYTES_2KB_ 2048
#define _BEBONE_MEMORY_BYTES_4KB_ 4096
#define _BEBONE_MEMORY_BYTES_8KB_ 8192

namespace bebone::core {
    /// Class used for allocating and managing an arena of memory
    class ArenaAllocator : private core::NonCopyable {
        private:
            void *_data;
            const size_t _capacity;
            size_t _allocated;

        public:
            /*!
             * Default constructor
             * @param size - desired arena size
            */
            explicit ArenaAllocator(const size_t& size);

            /*!
             * Default constructor
             * @param size - desired arena size
             * @param buffer - target arena buffer
            */
            explicit ArenaAllocator(const size_t& size, void* buffer);

            ~ArenaAllocator();

            /*!
             * Function that is used for allocating memory in arena
             * @param size - size of desired memory segment
             * @return Pointer to allocated memory segment
            */
            void* alloc(const size_t& size) noexcept;

            /*!
             * Function that is used for accessing an arena memory
             * @return Pointer to arena start
            */
            void* data() noexcept;

            /*!
             * Clears an arena
            */
            void clear() noexcept;

            /*!
             * Function that returns how much memory is already allocated in arena
             * @return Bytes allocated
            */
            [[nodiscard]] const size_t& allocated() const noexcept;

            /*!
             * Function that returns a total capacity of arena
             * @return Bytes capacity
            */
            [[nodiscard]] const size_t& capacity() const noexcept;
    };
}

#endif