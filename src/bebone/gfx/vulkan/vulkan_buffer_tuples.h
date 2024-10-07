#ifndef _BEBONE_GFX_VULKAN_BUFFER_TUPLES_H_
#define _BEBONE_GFX_VULKAN_BUFFER_TUPLES_H_

#include <vector>

#include "../gfx_backend.h"

#include "vulkan_buffer.h"

namespace bebone::gfx {
    class VulkanDevice;

    using namespace bebone::core;

    struct VulkanBufferMemoryTuple {
        public:
            std::unique_ptr<VulkanBuffer> buffer;
            std::unique_ptr<VulkanDeviceMemory> memory;

            VulkanBufferMemoryTuple(VulkanDevice& device, const size_t& size, VulkanBufferInfo buffer_info);

            template<typename T>
            VulkanBufferMemoryTuple(
                VulkanDevice& device,
                const std::vector<T>& data,
                VulkanBufferInfo buffer_info = {}
            ) {
                const auto size = sizeof(T) * data.size();

                buffer = std::make_unique<VulkanBuffer>(device, size, buffer_info);

                auto requirements = buffer->get_memory_requirements();

                memory = std::make_unique<VulkanDeviceMemory>(device, requirements, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT); // Todo this should be configurable
                memory->bind_buffer_memory(buffer);

                memory->upload_data(data.data(), size);
            }

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
        using type = std::unique_ptr<bebone::gfx::VulkanBuffer>;
    };

    template<>
    struct tuple_element<1, bebone::gfx::VulkanBufferMemoryTuple> {
        using type = std::unique_ptr<bebone::gfx::VulkanDeviceMemory>;
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
    struct tuple_size<std::unique_ptr<bebone::gfx::VulkanBufferMemoryTuple>>
            : std::integral_constant<std::size_t, 2> { };

    template<>
    struct tuple_element<0, std::unique_ptr<bebone::gfx::VulkanBufferMemoryTuple>> {
        using type = std::unique_ptr<bebone::gfx::VulkanBuffer>;
    };

    template<>
    struct tuple_element<1, std::unique_ptr<bebone::gfx::VulkanBufferMemoryTuple>> {
        using type = std::unique_ptr<bebone::gfx::VulkanDeviceMemory>;
    };
}

// Todo, why this needs to be in bebone::gfx namespace ?
namespace bebone::gfx {
    template<std::size_t i>
    auto get(const std::unique_ptr<bebone::gfx::VulkanBufferMemoryTuple>& tuple) {
        if constexpr (i == 0) {
            return tuple->buffer;
        } else if constexpr (i == 1) {
            return tuple->memory;
        } else {

        }
    }
}

#endif
