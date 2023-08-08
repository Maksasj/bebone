#ifndef _BEBONE_GFX_PIPELINE_H_
#define _BEBONE_GFX_PIPELINE_H_

#include <memory>

#include "pipeline_impl.h"

namespace bebone::gfx {
    class Pipeline {
        private:
            PipelineImpl* _impl;

            Pipeline(PipelineImpl* impl) : _impl(impl) {

            }

        public:
            ~Pipeline() {
                if(_impl != nullptr) {
                    delete _impl;
                }
            }


            PipelineImpl* get_impl() {
                return _impl;
            }

            template<class Impl, class... Args>
            static Pipeline create_from_impl(Args&&... args) {
                return Pipeline(new Impl(std::forward<Args>(args)...));
            }
    };
}

#endif
