#ifndef _BEBONE_GFX_VERTEX_BUFFER_H_
#define _BEBONE_GFX_VERTEX_BUFFER_H_

#include <memory>

#include "vulkan/vulkan_vertex_buffer_impl.h"

namespace bebone::gfx {
    template<class VertexType>
    class VertexBuffer {
        private:
            VulkanVertexBufferImpl<VertexType>* _impl;

        public:
            VertexBuffer(VulkanVertexBufferImpl<VertexType>* impl) : _impl(impl) {

            }

            ~VertexBuffer() {
                if(_impl != nullptr) {
                    delete _impl;
                }
            }

            VulkanVertexBufferImpl<VertexType>* get_impl() {
                return _impl;
            }
    };
}

#endif
