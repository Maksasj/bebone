#ifndef _BEBONE_GFX_INDEX_BUFFER_H_
#define _BEBONE_GFX_INDEX_BUFFER_H_

#include <memory>

#include "buffer_impl.h"

namespace bebone::gfx {
    class IndexBuffer {
        private:
            BufferImpl* _impl;

            IndexBuffer(BufferImpl* impl) : _impl(impl) {

            }

        public:
            ~IndexBuffer() {
                if(_impl != nullptr) {
                    delete _impl;
                }
            }

            BufferImpl* get_impl() {
                return _impl;
            }

            template<class Impl, class... Args>
            static IndexBuffer create_from_impl(Args&&... args) {
                return IndexBuffer(new Impl(std::forward<Args>(args)...));
            }
    };
}

#endif
