#ifndef _BEBONE_GFX_VULKAN_IMAGE_TUPLE_H_
#define _BEBONE_GFX_VULKAN_IMAGE_TUPLE_H_

#include <vector>

#include "../gfx_backend.h"
#include "vulkan_image.h"

namespace bebone::gfx {
        using namespace bebone::core;

        struct VulkanSwapChainImageTuple : public VulkanApi {
            std::shared_ptr<VulkanImage> image;
            std::shared_ptr<VulkanImageView> view;

            VulkanSwapChainImageTuple(
                const shared_ptr<VulkanImage>& image,
                const shared_ptr<VulkanImageView>& view);

            void destroy(VulkanDevice& device) override;
        };

        struct VulkanDepthImageTuple : public VulkanApi {
            std::shared_ptr<VulkanImage> image;
            std::shared_ptr<VulkanImageView> view;
            std::shared_ptr<VulkanDeviceMemory> memory;

            VulkanDepthImageTuple(
                const shared_ptr<VulkanImage>& image,
                const shared_ptr<VulkanImageView>& view,
                const shared_ptr<VulkanDeviceMemory>& memory);

            void destroy(VulkanDevice& device) override;
        };

        struct VulkanImageMemoryTuple : public VulkanApi {
            std::shared_ptr<VulkanImage> image;
            std::shared_ptr<VulkanDeviceMemory> memory;

            VulkanImageMemoryTuple(
                const shared_ptr<VulkanImage>& image,
                const shared_ptr<VulkanDeviceMemory>& memory);

            void destroy(VulkanDevice& device) override;
        };
}

// Note, this is a std template specialization and it is case-sensitive, please do not touch
namespace std {
    template<>
    struct tuple_size<bebone::gfx::VulkanSwapChainImageTuple>
            : std::integral_constant<std::size_t, 2> { };

    template<>
    struct tuple_element<0, bebone::gfx::VulkanSwapChainImageTuple> {
        using type = std::shared_ptr<bebone::gfx::VulkanImage>;
    };

    template<>
    struct tuple_element<1, bebone::gfx::VulkanSwapChainImageTuple> {
        using type = std::shared_ptr<bebone::gfx::VulkanImageView>;
    };
}

// Todo, why this needs to be in bebone::gfx namespace ?
namespace bebone::gfx {
    template<std::size_t i>
    auto get(const bebone::gfx::VulkanSwapChainImageTuple& tuple) {
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
    struct tuple_size<bebone::gfx::VulkanDepthImageTuple>
            : std::integral_constant<std::size_t, 3> { };

    template<>
    struct tuple_element<0, bebone::gfx::VulkanDepthImageTuple> {
        using type = std::shared_ptr<bebone::gfx::VulkanImage>;
    };

    template<>
    struct tuple_element<1, bebone::gfx::VulkanDepthImageTuple> {
        using type = std::shared_ptr<bebone::gfx::VulkanImageView>;
    };

    template<>
    struct tuple_element<2, bebone::gfx::VulkanDepthImageTuple> {
        using type = std::shared_ptr<bebone::gfx::VulkanDeviceMemory>;
    };
}

// Todo, why this needs to be in bebone::gfx namespace ?
namespace bebone::gfx {
    template<std::size_t i>
    auto get(const bebone::gfx::VulkanDepthImageTuple& tuple) {
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
    struct tuple_size<bebone::gfx::VulkanImageMemoryTuple>
            : std::integral_constant<std::size_t, 2> { };

    template<>
    struct tuple_element<0, bebone::gfx::VulkanImageMemoryTuple> {
        using type = std::shared_ptr<bebone::gfx::VulkanImage>;
    };

    template<>
    struct tuple_element<1, bebone::gfx::VulkanImageMemoryTuple> {
        using type = std::shared_ptr<bebone::gfx::VulkanDeviceMemory>;
    };
}

// Todo, why this needs to be in bebone::gfx namespace ?
namespace bebone::gfx {
    template<std::size_t i>
    auto get(const bebone::gfx::VulkanImageMemoryTuple& tuple) {
        if constexpr (i == 0) {
            return tuple.image;
        } else if constexpr (i == 1) {
            return tuple.memory;
        } else {

        }
    }
}

#endif
