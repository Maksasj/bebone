#ifndef _BEBONE_RENDERER_IUNIFORM_BUFFER_H_
#define _BEBONE_RENDERER_IUNIFORM_BUFFER_H_

#include "iuniform_buffer_impl.h"

namespace bebone::renderer {
    using namespace bebone::core;

    class IUniformBuffer : private NonCopyable {
        private:
            std::shared_ptr<IUniformBufferImpl> impl;

        public:
            IUniformBuffer(const std::shared_ptr<IUniformBufferImpl>& impl);

            void upload_data(void* src, const size_t& size);

            UniformBufferHandle get_handle() const;
    };
}

#endif
