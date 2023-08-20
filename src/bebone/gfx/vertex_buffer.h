#ifndef _BEBONE_GFX_VERTEX_BUFFER_H_
#define _BEBONE_GFX_VERTEX_BUFFER_H_

#include <memory>

#include "vulkan/vulkan_vertex_buffer_impl.h"

namespace bebone::gfx {
    class VertexBuffer {
        private:
            VulkanVertexBufferImpl* _impl;

            VertexBuffer(VulkanVertexBufferImpl* impl) : _impl(impl) {

            }

        public:
            ~VertexBuffer() {
                if(_impl != nullptr) {
                    delete _impl;
                }
            }

            VulkanVertexBufferImpl* get_impl() {
                return _impl;
            }

            template<class Impl, class... Args>
            static VertexBuffer create_from_impl(Args&&... args) {
                return VertexBuffer(new Impl(std::forward<Args>(args)...));
            }
    };
}

#endif
