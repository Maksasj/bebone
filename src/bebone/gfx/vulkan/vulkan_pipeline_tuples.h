#ifndef BEBONE_VULKAN_PIPELINE_TUPLES_H
#define BEBONE_VULKAN_PIPELINE_TUPLES_H

#include "../gfx_backend.h"

#include "vulkan_pipeline.h"
#include "vulkan_descriptor_set.h"

namespace bebone::gfx {
    class VulkanConstRange;

    struct VulkanTexture;
    struct VulkanBufferMemoryTuple;

    using VulkanBindlessHandle = size_t; // Todo

    struct VulkanManagedPipelineTuple : public VulkanApi {
        public:
            std::shared_ptr<VulkanPipeline> pipeline;
            std::shared_ptr<VulkanPipelineLayout> layout;
            std::vector<std::shared_ptr<VulkanDescriptorSet>> descriptors;

        private:
            size_t bindless_samplers_index;
            size_t bindless_uniforms_index;

        public:
            VulkanManagedPipelineTuple(
                const shared_ptr<VulkanPipeline>& pipeline,
                const shared_ptr<VulkanPipelineLayout>& layout,
                const std::vector<std::shared_ptr<VulkanDescriptorSet>>& descriptors);

            VulkanBindlessHandle bind_texture(
                std::shared_ptr<VulkanDevice>& device,
                std::shared_ptr<VulkanTexture>& texture,
                const size_t& binding);

            std::vector<VulkanBindlessHandle> bind_uniform_buffer(
                std::shared_ptr<VulkanDevice>& device,
                const std::vector<VulkanBufferMemoryTuple>& tuples,
                const size_t& binding);

            void destroy(VulkanDevice& device) override;
    };
}

// Note, this is a std template specialization and it is case-sensitive, please do not touch
namespace std {
    template<>
    struct tuple_size<bebone::gfx::VulkanManagedPipelineTuple>
        : std::integral_constant<std::size_t, 3> { };

    template<>
    struct tuple_element<0, bebone::gfx::VulkanManagedPipelineTuple> {
        using type = std::shared_ptr<bebone::gfx::VulkanPipeline>;
    };

    template<>
    struct tuple_element<1, bebone::gfx::VulkanManagedPipelineTuple> {
        using type = std::shared_ptr<bebone::gfx::VulkanPipelineLayout>;
    };

    template<>
    struct tuple_element<2, bebone::gfx::VulkanManagedPipelineTuple> {
        using type = std::vector<std::shared_ptr<bebone::gfx::VulkanDescriptorSet>>;
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
        } else if constexpr (i == 2) {
            return tuple.descriptors;
        } else {

        }
    }
}

#endif
