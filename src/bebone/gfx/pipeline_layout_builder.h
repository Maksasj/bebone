#ifndef _BEBONE_GFX_PIPELINE_LAYOUT_BUILDER_H_
#define _BEBONE_GFX_PIPELINE_LAYOUT_BUILDER_H_

#include <memory>

// #include "pipeline_layout.h"
#include "pipeline_layout_builder_impl.h"
#include "gpu_resource_manager.h"

namespace bebone::gfx {
    class PipelineLayoutBuilder {
        private:
            PipelineLayoutBuilderImpl* _impl;

            PipelineLayoutBuilder(PipelineLayoutBuilderImpl* impl) : _impl(impl) {
                
            }

        public:
            ~PipelineLayoutBuilder() {
                delete _impl;
            }

            PipelineLayoutBuilder& set_constant_range(const size_t& offset, const size_t& size) {
                _impl->set_constant_range(offset, size);
                return *this;
            }

            // PipelineLayout build(GPUResourceManager& _gpuResourceManager) {
            //     return _impl->build(_gpuResourceManager);
            // }

            PipelineLayoutBuilderImpl* get_impl() {
                return _impl;
            }

            template<class Impl, class... Args>
            static PipelineLayoutBuilder create_from_impl(Args&&... args) {
                return PipelineLayoutBuilder(new Impl(std::forward<Args>(args)...));
            }
    };
}

#endif
