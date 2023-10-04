#ifndef _BEBONE_GFX_PIPELINE_LAYOUT_BUILDER_IMPLEMENTATION_H_
#define _BEBONE_GFX_PIPELINE_LAYOUT_BUILDER_IMPLEMENTATION_H_

#include <memory>

#include "pipeline_layout.h"
#include "texture.h"

#include "vulkan/vulkan_descriptor_pool.h"

#include "gpu_resource_manager.h"

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
