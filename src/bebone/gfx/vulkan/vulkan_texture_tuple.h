#ifndef _BEBONE_GFX_VULKAN_TEXTURE_TUPLE_H_
#define _BEBONE_GFX_VULKAN_TEXTURE_TUPLE_H_

#include <vector>

#include "../gfx_backend.h"

#include "../../assets/image/image.h"

#include "vulkan_image.h"
#include "vulkan_sampler.h"
#include "vulkan_image_view.h"
#include "vulkan_attachment.h"

namespace bebone::gfx {
    class VulkanDevice;

    using namespace bebone::core;

    struct VulkanTextureTuple : public IVulkanAttachment, private core::NonCopyable {
        std::shared_ptr<VulkanImage> image;
        std::shared_ptr<VulkanDeviceMemory> memory;
        std::shared_ptr<VulkanImageView> view;
        std::shared_ptr<VulkanSampler> sampler;

        public:
            VulkanTextureTuple( // Constructors that require VulkanDevice& need to protected
                VulkanDevice& device,
                const std::shared_ptr<assets::Image<ColorRGBA>>& raw);

            VulkanTextureTuple(
                const std::shared_ptr<VulkanImage>& image,
                const std::shared_ptr<VulkanDeviceMemory>& memory,
                const std::shared_ptr<VulkanImageView>& view,
                const std::shared_ptr<VulkanSampler>& sampler);

            VulkanTextureTuple(
                VulkanDevice& device,
                VkExtent3D extent,
                VkFormat image_format);

            std::optional<std::shared_ptr<VulkanImage>> get_image() override;
            std::optional<std::shared_ptr<VulkanImageView>> get_view() override;
            std::optional<std::shared_ptr<VulkanDeviceMemory>> get_memory() override;
            std::optional<std::shared_ptr<VulkanSampler>> get_sampler() override;

            VulkanAttachmentType get_type() const override;

            void destroy(VulkanDevice& device) override;
    };
}

// Note, this is a std template specialization and it is case-sensitive, please do not touch
namespace std {
    template<>
    struct tuple_size<bebone::gfx::VulkanTextureTuple>
            : std::integral_constant<std::size_t, 4> { };

    template<>
    struct tuple_element<0, bebone::gfx::VulkanTextureTuple> {
        using type = std::shared_ptr<bebone::gfx::VulkanImage>;
    };

    template<>
    struct tuple_element<1, bebone::gfx::VulkanTextureTuple> {
        using type = std::shared_ptr<bebone::gfx::VulkanDeviceMemory>;
    };

    template<>
    struct tuple_element<2, bebone::gfx::VulkanTextureTuple> {
        using type = std::shared_ptr<bebone::gfx::VulkanImageView>;
    };

    template<>
    struct tuple_element<3, bebone::gfx::VulkanTextureTuple> {
        using type = std::shared_ptr<bebone::gfx::VulkanSampler>;
    };
}

// Todo, why this needs to be in bebone::gfx namespace ?
namespace bebone::gfx {
    template<std::size_t i>
    auto get(const bebone::gfx::VulkanTextureTuple& tuple) {
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
