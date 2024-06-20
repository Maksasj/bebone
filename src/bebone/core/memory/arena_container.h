#ifndef _BEBONE_CORE_ARENA_CONTAINER_H_
#define _BEBONE_CORE_ARENA_CONTAINER_H_

#include "noncopyable.h"
#include "arena_allocator.h"

namespace bebone::core {
    /// Container class that can store values of different types by their value
    class ArenaContainer : private core::NonCopyable {
        private:
            ArenaAllocator data;
            ArenaAllocator indices;

        public:
            /*!
             * Default constructor
             * @param size - desired arena size
            */
            explicit ArenaContainer(const size_t& size);

            /*!
             * Function that allocated a memory segment of given size
             * @param size - size of desired memory segment
             * @return Pointer to allocated memory segment
            */
            void* alloc(const size_t& size) noexcept;

            /*!
             * Function that is used for indexing and specific allocating index
             * @param index desired allocation index
             * @return Pointer to allocation
            */
            void* at(const size_t& index);

            /*!
             * Function that clears container
            */
            void clear() noexcept;

            /*!
             * Function that returns number of allocations in this container
             * @return Allocation count
            */
            [[nodiscard]] size_t size() const noexcept;

            /*!
             * Function that returns how much memory is already allocated in arena
             * @return Bytes allocated
            */
            [[nodiscard]] size_t allocated() const noexcept;

            /*!
             * Function that returns a total capacity of arena
             * @return Bytes capacity
            */
            [[nodiscard]] size_t capacity() const noexcept;
    };
}

#endif