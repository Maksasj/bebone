#ifndef _BEBONE_GFX_PIPELINE_LAYOUT_BUILDER_H_
#define _BEBONE_GFX_PIPELINE_LAYOUT_BUILDER_H_

#include <memory>

#include "pipeline_layout.h"
#include "pipeline_layout_builder_impl.h"

/*
    // Pipeline layout builder atomatically insuers that all buffers have been craeted with proper count
    PipelineLayoutBuilder pipelineLayoutBuilder = renderer.create_pipeline_layout_builder();

        // x.add_uniform_buffer(binding, size)
        pipelineLayoutBuilder.bind_uniform_buffer(0, sizeof(float));
        pipelineLayoutBuilder.bind_uniform_buffer(1, sizeof(float) * 2);

    PipelineLayout pipelineLayout = pipelineLayoutBuilder.build();

*/

namespace bebone::gfx {
    class PipelineLayoutBuilder {
        private:
            PipelineLayoutBuilderImpl* _impl;

            PipelineLayoutBuilder(PipelineLayoutBuilderImpl* impl) : _impl(impl) {
                
            }
            
        public:
            void bind_uniform_buffer(const size_t& binding, UniformBuffer& buffer) {
                _impl->bind_uniform_buffer(binding, buffer);
            }

            PipelineLayout build() {
                return _impl->build();
            }

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
