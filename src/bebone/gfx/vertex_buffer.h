#ifndef _BEBONE_GFX_VERTEX_BUFFER_H_
#define _BEBONE_GFX_VERTEX_BUFFER_H_

#include <memory>

#include "vertex_buffer_impl.h"

namespace bebone::gfx {
    class VertexBuffer {
        private:
            VertexBufferImpl* _impl;

            VertexBuffer(VertexBufferImpl* impl) : _impl(impl) {

            }

        public:
            ~VertexBuffer() {
                if(_impl != nullptr) {
                    delete _impl;
                }
            }

            VertexBufferImpl* get_impl() {
                return _impl;
            }

            template<class Impl, class... Args>
            static VertexBuffer create_from_impl(Args&&... args) {
                return VertexBuffer(new Impl(std::forward<Args>(args)...));
            }
    };
}

#endif
