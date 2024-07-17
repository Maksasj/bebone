#ifndef BEBONE_VULKAN_PIPELINE_TUPLES_H
#define BEBONE_VULKAN_PIPELINE_TUPLES_H

#include "../gfx_backend.h"

#include "vulkan_pipeline.h"
#include "vulkan_descriptor_set.h"

namespace bebone::gfx {
    class VulkanConstRange;

    struct VulkanTextureTuple;
    class IVulkanAttachment;
    struct VulkanBufferMemoryTuple;

    using VulkanBindlessHandle = size_t; // Todo

    struct VulkanManagedPipelineTuple : public VulkanApi {
        public:
            std::shared_ptr<VulkanPipeline> pipeline;
            std::shared_ptr<VulkanPipelineLayout> layout;

        public:
            VulkanManagedPipelineTuple(
                const shared_ptr<VulkanPipeline>& pipeline,
                const shared_ptr<VulkanPipelineLayout>& layout);

            /*
            VulkanBindlessHandle bind_texture(
                std::shared_ptr<VulkanDevice>& device,
                std::shared_ptr<VulkanTextureTuple>& texture,
                const size_t& binding);

            std::vector<VulkanBindlessHandle> bind_textures(
                std::shared_ptr<VulkanDevice>& device,
                std::vector<std::shared_ptr<VulkanTextureTuple>>& texture,
                const size_t& binding);

            VulkanBindlessHandle bind_attachment(
                std::shared_ptr<VulkanDevice>& device,
                std::shared_ptr<IVulkanAttachment>& attachment,
                const size_t& binding);

            std::vector<VulkanBindlessHandle> bind_attachments(
                std::shared_ptr<VulkanDevice>& device,
                std::vector<std::shared_ptr<IVulkanAttachment>>& attachments,
                const size_t& binding);

            std::vector<VulkanBindlessHandle> bind_uniform_buffer(
                std::shared_ptr<VulkanDevice>& device,
                const std::vector<std::shared_ptr<VulkanBufferMemoryTuple>>& tuples,
                const size_t& binding);
            */

            void destroy(VulkanDevice& device) override;
    };
}

// Note, this is a std template specialization and it is case-sensitive, please do not touch
namespace std {
    template<>
    struct tuple_size<bebone::gfx::VulkanManagedPipelineTuple>
        : std::integral_constant<std::size_t, 2> { };

    template<>
    struct tuple_element<0, bebone::gfx::VulkanManagedPipelineTuple> {
        using type = std::shared_ptr<bebone::gfx::VulkanPipeline>;
    };

    template<>
    struct tuple_element<1, bebone::gfx::VulkanManagedPipelineTuple> {
        using type = std::shared_ptr<bebone::gfx::VulkanPipelineLayout>;
    };
}

// Todo, why this needs to be in bebone::gfx namespace ?
namespace bebone::gfx {
    template<std::size_t i>
    auto get(const bebone::gfx::VulkanManagedPipelineTuple& tuple) {
        if constexpr (i == 0) {
            return tuple.pipeline;
        } else if constexpr (i == 1) {
            return tuple.layout;
        } else {

        }
    }
}

#endif
