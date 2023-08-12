#ifndef _BEBONE_GFX_PIPELINE_LAYOUT_H_
#define _BEBONE_GFX_PIPELINE_LAYOUT_H_

#include <memory>

#include "pipeline_layout_impl.h"

namespace bebone::gfx {
    class PipelineLayout {
        private:
            PipelineLayoutImpl* _impl;

            PipelineLayout(PipelineLayoutImpl* impl) : _impl(impl) {
                
            }

        public:
            ~PipelineLayout() {
                if(_impl != nullptr) {
                    delete _impl;
                }
            }

            PipelineLayoutImpl* get_impl() {
                return _impl;
            }

            template<class Impl, class... Args>
            static PipelineLayout create_from_impl(Args&&... args) {
                return PipelineLayout(new Impl(std::forward<Args>(args)...));
            }
    };
}

#endif
