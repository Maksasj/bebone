#ifndef _BEBONE_GFX_PIPELINE_H_
#define _BEBONE_GFX_PIPELINE_H_

#include <memory>

#include "vulkan/vulkan_pipeline_impl.h"

namespace bebone::gfx {
    class Pipeline {
        private:
            VulkanPipeline** _impl;

        public:
            Pipeline(VulkanPipeline** impl) : _impl(impl) {

            }

            VulkanPipeline* get_impl() {
                return *_impl;
            }
    };
}

#endif
