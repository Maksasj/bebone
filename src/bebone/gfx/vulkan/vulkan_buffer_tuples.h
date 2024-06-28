#ifndef _BEBONE_GFX_VULKAN_BUFFER_TUPLES_H_
#define _BEBONE_GFX_VULKAN_BUFFER_TUPLES_H_

#include <vector>

#include "../gfx_backend.h"

#include "vulkan_buffer.h"

namespace bebone::gfx::vulkan {
    using namespace bebone::core;

    struct VulkanBufferMemoryTuple : public VulkanApi {
        public:
            std::shared_ptr<VulkanBuffer> buffer;
            std::shared_ptr<VulkanDeviceMemory> memory;

            VulkanBufferMemoryTuple( // Todo this constructor should be moved to protected, or no ?
                const shared_ptr<VulkanBuffer>& buffer,
                const shared_ptr<VulkanDeviceMemory>& memory);

            void upload_data(
                std::shared_ptr<VulkanDevice>& device,
                const void* src,
                const size_t& size);

            void upload_data(
                VulkanDevice& device,
                const void* src,
                const size_t& size);

            void destroy(VulkanDevice& device) override;
    };
}

// Todo, do we really need code below ?

// Note, this is a std template specialization and it is case-sensitive, please do not touch
namespace std {
    template<>
    struct tuple_size<bebone::gfx::vulkan::VulkanBufferMemoryTuple>
            : std::integral_constant<std::size_t, 2> { };

    template<>
    struct tuple_element<0, bebone::gfx::vulkan::VulkanBufferMemoryTuple> {
        using type = std::shared_ptr<bebone::gfx::vulkan::VulkanBuffer>;
    };

    template<>
    struct tuple_element<1, bebone::gfx::vulkan::VulkanBufferMemoryTuple> {
        using type = std::shared_ptr<bebone::gfx::vulkan::VulkanDeviceMemory>;
    };
}

// Todo, why this needs to be in bebone::gfx::vulkan namespace ?
namespace bebone::gfx::vulkan {
    template<std::size_t i>
    auto get(const bebone::gfx::vulkan::VulkanBufferMemoryTuple& tuple) {
        if constexpr (i == 0) {
            return tuple.buffer;
        } else if constexpr (i == 1) {
            return tuple.memory;
        } else {

        }
    }
}

#endif
