#ifndef _BEBONE_GFX_UNIFORM_BUFFER_H_
#define _BEBONE_GFX_UNIFORM_BUFFER_H_

#include <memory>

#include "buffer_impl.h"

namespace bebone::gfx {
    class UniformBuffer {
        private:
            BufferImpl* _impl;

            UniformBuffer(BufferImpl* impl) : _impl(impl) {

            }

        public:
            ~UniformBuffer() {
                if(_impl != nullptr) {
                    delete _impl;
                }
            }

            BufferImpl* get_impl() {
                return _impl;
            }

            template<class Impl, class... Args>
            static UniformBuffer create_from_impl(Args&&... args) {
                return UniformBuffer(new Impl(std::forward<Args>(args)...));
            }
    };
}

#endif
