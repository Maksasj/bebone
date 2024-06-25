#ifndef _BEBONE_GFX_VULKAN_IMAGE_TUPLE_H_
#define _BEBONE_GFX_VULKAN_IMAGE_TUPLE_H_

#include <vector>

#include "../gfx_backend.h"
#include "vulkan_image.h"

namespace bebone::gfx::vulkan {
        using namespace bebone::core;

        struct VulkanSwapChainImageTuple : public VulkanApi {
            std::shared_ptr<VulkanImage> image;
            std::shared_ptr<VulkanImageView> view;

            VulkanSwapChainImageTuple(
                const shared_ptr<VulkanImage>& image,
                const shared_ptr<VulkanImageView>& view);

            void destroy(VulkanDevice &device) override;
        };

        struct VulkanDepthImageTuple : public VulkanApi {
            std::shared_ptr<VulkanImage> image;
            std::shared_ptr<VulkanImageView> view;
            std::shared_ptr<VulkanDeviceMemory> memory;

            VulkanDepthImageTuple(
                const shared_ptr<VulkanImage>& image,
                const shared_ptr<VulkanImageView>& view,
                const shared_ptr<VulkanDeviceMemory>& memory);

            void destroy(VulkanDevice &device) override;
        };

        struct VulkanImageMemoryTuple : public VulkanApi {
            std::shared_ptr<VulkanImage> image;
            std::shared_ptr<VulkanDeviceMemory> memory;

            VulkanImageMemoryTuple(
                const shared_ptr<VulkanImage>& image,
                const shared_ptr<VulkanDeviceMemory>& memory);

            void destroy(VulkanDevice &device) override;
        };
}

// Note, this is a std template specialization and it is case-sensitive, please do not touch
namespace std {
    template<>
    struct tuple_size<bebone::gfx::vulkan::VulkanSwapChainImageTuple>
            : std::integral_constant<std::size_t, 2> { };

    template<>
    struct tuple_element<0, bebone::gfx::vulkan::VulkanSwapChainImageTuple> {
        using type = std::shared_ptr<bebone::gfx::vulkan::VulkanImage>;
    };

    template<>
    struct tuple_element<1, bebone::gfx::vulkan::VulkanSwapChainImageTuple> {
        using type = std::shared_ptr<bebone::gfx::vulkan::VulkanImageView>;
    };
}

// Todo, why this needs to be in bebone::gfx::vulkan namespace ?
namespace bebone::gfx::vulkan {
    template<std::size_t i>
    auto get(const bebone::gfx::vulkan::VulkanSwapChainImageTuple& tuple) {
        if constexpr (i == 0) {
            return tuple.image;
        } else if constexpr (i == 1) {
            return tuple.view;
        } else {

        }
    }
}

// Note, this is a std template specialization and it is case-sensitive, please do not touch
namespace std {
    template<>
    struct tuple_size<bebone::gfx::vulkan::VulkanDepthImageTuple>
            : std::integral_constant<std::size_t, 3> { };

    template<>
    struct tuple_element<0, bebone::gfx::vulkan::VulkanDepthImageTuple> {
        using type = std::shared_ptr<bebone::gfx::vulkan::VulkanImage>;
    };

    template<>
    struct tuple_element<1, bebone::gfx::vulkan::VulkanDepthImageTuple> {
        using type = std::shared_ptr<bebone::gfx::vulkan::VulkanImageView>;
    };

    template<>
    struct tuple_element<2, bebone::gfx::vulkan::VulkanDepthImageTuple> {
        using type = std::shared_ptr<bebone::gfx::vulkan::VulkanDeviceMemory>;
    };
}

// Todo, why this needs to be in bebone::gfx::vulkan namespace ?
namespace bebone::gfx::vulkan {
    template<std::size_t i>
    auto get(const bebone::gfx::vulkan::VulkanDepthImageTuple& tuple) {
        if constexpr (i == 0) {
            return tuple.image;
        } else if constexpr (i == 1) {
            return tuple.view;
        } else if constexpr (i == 2) {
            return tuple.memory;
        } else {

        }
    }
}

// Note, this is a std template specialization and it is case-sensitive, please do not touch
namespace std {
    template<>
    struct tuple_size<bebone::gfx::vulkan::VulkanImageMemoryTuple>
            : std::integral_constant<std::size_t, 2> { };

    template<>
    struct tuple_element<0, bebone::gfx::vulkan::VulkanImageMemoryTuple> {
        using type = std::shared_ptr<bebone::gfx::vulkan::VulkanImage>;
    };

    template<>
    struct tuple_element<1, bebone::gfx::vulkan::VulkanImageMemoryTuple> {
        using type = std::shared_ptr<bebone::gfx::vulkan::VulkanDeviceMemory>;
    };
}

// Todo, why this needs to be in bebone::gfx::vulkan namespace ?
namespace bebone::gfx::vulkan {
    template<std::size_t i>
    auto get(const bebone::gfx::vulkan::VulkanImageMemoryTuple& tuple) {
        if constexpr (i == 0) {
            return tuple.image;
        } else if constexpr (i == 1) {
            return tuple.memory;
        } else {

        }
    }
}

#endif
