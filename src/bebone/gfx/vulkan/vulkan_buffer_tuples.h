#ifndef _BEBONE_GFX_VULKAN_BUFFER_TUPLES_H_
#define _BEBONE_GFX_VULKAN_BUFFER_TUPLES_H_

#include <vector>

#include "../gfx_backend.h"

#include "vulkan_buffer.h"

namespace bebone::gfx {
    using namespace bebone::core;

    struct VulkanBufferMemoryTuple : public VulkanApi {
        public:
            std::shared_ptr<VulkanBuffer> buffer;
            std::shared_ptr<VulkanDeviceMemory> memory;

            VulkanBufferMemoryTuple(const shared_ptr<VulkanBuffer>& buffer, const shared_ptr<VulkanDeviceMemory>& memory);

            void upload_data(const void* src, const size_t& size);
    };
}

// Todo, do we really need code below ?

// Note, this is a std template specialization and it is case-sensitive, please do not touch
namespace std {
    template<>
    struct tuple_size<bebone::gfx::VulkanBufferMemoryTuple>
            : std::integral_constant<std::size_t, 2> { };

    template<>
    struct tuple_element<0, bebone::gfx::VulkanBufferMemoryTuple> {
        using type = std::shared_ptr<bebone::gfx::VulkanBuffer>;
    };

    template<>
    struct tuple_element<1, bebone::gfx::VulkanBufferMemoryTuple> {
        using type = std::shared_ptr<bebone::gfx::VulkanDeviceMemory>;
    };
}

// Todo, why this needs to be in bebone::gfx namespace ?
namespace bebone::gfx {
    template<std::size_t i>
    auto get(const bebone::gfx::VulkanBufferMemoryTuple& tuple) {
        if constexpr (i == 0) {
            return tuple.buffer;
        } else if constexpr (i == 1) {
            return tuple.memory;
        } else {

        }
    }
}

// Note, this is a std template specialization and it is case-sensitive, please do not touch
namespace std {
    template<>
    struct tuple_size<std::shared_ptr<bebone::gfx::VulkanBufferMemoryTuple>>
            : std::integral_constant<std::size_t, 2> { };

    template<>
    struct tuple_element<0, std::shared_ptr<bebone::gfx::VulkanBufferMemoryTuple>> {
        using type = std::shared_ptr<bebone::gfx::VulkanBuffer>;
    };

    template<>
    struct tuple_element<1, std::shared_ptr<bebone::gfx::VulkanBufferMemoryTuple>> {
        using type = std::shared_ptr<bebone::gfx::VulkanDeviceMemory>;
    };
}

// Todo, why this needs to be in bebone::gfx namespace ?
namespace bebone::gfx {
    template<std::size_t i>
    auto get(const std::shared_ptr<bebone::gfx::VulkanBufferMemoryTuple>& tuple) {
        if constexpr (i == 0) {
            return tuple->buffer;
        } else if constexpr (i == 1) {
            return tuple->memory;
        } else {

        }
    }
}

#endif
