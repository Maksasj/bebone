#ifndef _BEBONE_GFX_PIPELINE_LAYOUT_BUILDER_IMPLEMENTATION_H_
#define _BEBONE_GFX_PIPELINE_LAYOUT_BUILDER_IMPLEMENTATION_H_

#include <memory>

#include "pipeline_layout.h"
#include "texture.h"

#include "vulkan/vulkan_descriptor_pool.h"

#include "gpu_resource_manager.h"

/*
    // Pipeline layout builder atomatically insuers that all buffers have been craeted with proper count
    PipelineLayoutBuilder pipelineLayoutBuilder = renderer.create_pipeline_layout_builder();

        // x.add_uniform_buffer(binding, size)
        pipelineLayoutBuilder.bind_uniform_buffer(0, sizeof(float));
        pipelineLayoutBuilder.bind_uniform_buffer(1, sizeof(float) * 2);

    PipelineLayout pipelineLayout = pipelineLayoutBuilder.build();

*/

namespace bebone::gfx {
    class PipelineLayoutBuilderImpl {
        private:

        public:
            virtual ~PipelineLayoutBuilderImpl() {}
            
            virtual void set_constant_range(const size_t& offset, const size_t& size) = 0;

            virtual PipelineLayout build(GPUResourceManager& _gpuResourceManager) = 0;
    };
}

#endif
