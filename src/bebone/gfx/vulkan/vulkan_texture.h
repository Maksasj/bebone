#ifndef _BEBONE_GFX_VULKAN_TEXTURE_H_
#define _BEBONE_GFX_VULKAN_TEXTURE_H_

#include <vector>

#include "../gfx_backend.h"

#include "../../assets/image/image.h"

#include "vulkan_image.h"
#include "vulkan_sampler.h"
#include "vulkan_image_view.h"

namespace bebone::gfx {
    class VulkanDevice;

    using namespace bebone::core;

    struct VulkanTexture : public VulkanApi, private core::NonCopyable {
        std::shared_ptr<VulkanImage> image;
        std::shared_ptr<VulkanDeviceMemory> memory;
        std::shared_ptr<VulkanImageView> view;
        std::shared_ptr<VulkanSampler> sampler;

        public:
            VulkanTexture( // Constructors that require VulkanDevice& need to protected
                VulkanDevice& device,
                std::shared_ptr<VulkanCommandBufferPool>& command_buffer_pool,
                const std::shared_ptr<assets::Image<ColorRGBA>>& raw);

            VulkanTexture(
                VulkanDevice& device,
                std::shared_ptr<VulkanCommandBufferPool>& command_buffer_pool,
                const size_t& width,
                const size_t& height);

            void destroy(VulkanDevice& device) override;
    };
}

// Note, this is a std template specialization and it is case-sensitive, please do not touch
namespace std {
    template<>
    struct tuple_size<bebone::gfx::VulkanTexture>
            : std::integral_constant<std::size_t, 4> { };

    template<>
    struct tuple_element<0, bebone::gfx::VulkanTexture> {
        using type = std::shared_ptr<bebone::gfx::VulkanImage>;
    };

    template<>
    struct tuple_element<1, bebone::gfx::VulkanTexture> {
        using type = std::shared_ptr<bebone::gfx::VulkanDeviceMemory>;
    };

    template<>
    struct tuple_element<2, bebone::gfx::VulkanTexture> {
        using type = std::shared_ptr<bebone::gfx::VulkanImageView>;
    };

    template<>
    struct tuple_element<3, bebone::gfx::VulkanTexture> {
        using type = std::shared_ptr<bebone::gfx::VulkanSampler>;
    };
}

// Todo, why this needs to be in bebone::gfx namespace ?
namespace bebone::gfx {
    template<std::size_t i>
    auto get(const bebone::gfx::VulkanTexture& tuple) {
        if constexpr (i == 0) {
            return tuple.image;
        } else if constexpr (i == 1) {
            return tuple.memory;
        } else if constexpr (i == 2) {
            return tuple.view;
        } else if constexpr (i == 3) {
            return tuple.sampler;
        } else {

        }
    }
}

#endif
