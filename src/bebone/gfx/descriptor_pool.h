#ifndef _BEBONE_GFX_DESCRIPTOR_POOL_H_
#define _BEBONE_GFX_DESCRIPTOR_POOL_H_

#include "../core/arena_allocator.h"

#include "gfx_backend.h"

namespace bebone::gfx {
    class DescriptorPool {
        private:

        public:
            virtual ~DescriptorPool() {}

            virtual VkDescriptorSet& get_descriptor_set(const size_t& index) = 0;
    };
}

#endif
