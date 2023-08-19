#ifndef _BEBONE_GFX_VERTEX_BUFFER_H_
#define _BEBONE_GFX_VERTEX_BUFFER_H_

#include <memory>

#include "vulkan/vulkan_buffer_impl.h"

#include "vulkan/vulkan_buffer_impl.h"

namespace bebone::gfx {
    class VertexBuffer {
        private:
            VulkanBufferImpl* _impl;

            VertexBuffer(VulkanBufferImpl* impl) : _impl(impl) {

            }

        public:
            ~VertexBuffer() {
                if(_impl != nullptr) {
                    delete _impl;
                }
            }

            VulkanBufferImpl* get_impl() {
                return _impl;
            }

            template<class Impl, class... Args>
            static VertexBuffer create_from_impl(Args&&... args) {
                return VertexBuffer(new Impl(std::forward<Args>(args)...));
            }
    };
}

#endif
