#ifndef _BEBONE_GFX_VULKAN_TEXTURE_H_
#define _BEBONE_GFX_VULKAN_TEXTURE_H_

#include <vector>

#include "../gfx_backend.h"

#include "../../assets/image/image.h"

#include "vulkan_image.h"
#include "vulkan_sampler.h"
#include "vulkan_image_view.h"

namespace bebone::gfx::vulkan {
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

            void destroy(VulkanDevice& device) override;
    };
}

// Note, this is a std template specialization and it is case-sensitive, please do not touch
namespace std {
    template<>
    struct tuple_size<bebone::gfx::vulkan::VulkanTexture>
            : std::integral_constant<std::size_t, 4> { };

    template<>
    struct tuple_element<0, bebone::gfx::vulkan::VulkanTexture> {
        using type = std::shared_ptr<bebone::gfx::vulkan::VulkanImage>;
    };

    template<>
    struct tuple_element<1, bebone::gfx::vulkan::VulkanTexture> {
        using type = std::shared_ptr<bebone::gfx::vulkan::VulkanDeviceMemory>;
    };

    template<>
    struct tuple_element<2, bebone::gfx::vulkan::VulkanTexture> {
        using type = std::shared_ptr<bebone::gfx::vulkan::VulkanImageView>;
    };

    template<>
    struct tuple_element<3, bebone::gfx::vulkan::VulkanTexture> {
        using type = std::shared_ptr<bebone::gfx::vulkan::VulkanSampler>;
    };
}

// Todo, why this needs to be in bebone::gfx::vulkan namespace ?
namespace bebone::gfx::vulkan {
    template<std::size_t i>
    auto get(const bebone::gfx::vulkan::VulkanTexture& tuple) {
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
