#ifndef _BEBONE_GFX_INDEX_BUFFER_H_
#define _BEBONE_GFX_INDEX_BUFFER_H_

#include <memory>

#include "vulkan/vulkan_buffer_impl.h"

namespace bebone::gfx {
    class IndexBuffer {
        private:
            VulkanBufferImpl* _impl;

        public:
            IndexBuffer(VulkanBufferImpl* impl) : _impl(impl) {

            }

            ~IndexBuffer() {
                if(_impl != nullptr) {
                    delete _impl;
                }
            }

            VulkanBufferImpl* get_impl() {
                return _impl;
            }
    };
}

#endif
