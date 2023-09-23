#ifndef _BEBONE_GFX_VERTEX_BUFFER_H_
#define _BEBONE_GFX_VERTEX_BUFFER_H_

#include <memory>

#include "vulkan/vulkan_vertex_buffer_impl.h"

namespace bebone::gfx {
    class VertexBuffer {
        private:
            VulkanVertexBufferImpl* _impl;

        public:
            VertexBuffer(VulkanVertexBufferImpl* impl) : _impl(impl) {

            }

            ~VertexBuffer() {
                if(_impl != nullptr) {
                    delete _impl;
                }
            }

            VulkanVertexBufferImpl* get_impl() {
                return _impl;
            }
    };
}

#endif
