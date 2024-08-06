#ifndef _BEBONE_RENDERER_IUNIFORM_BUFFER_IMPL_H_
#define _BEBONE_RENDERER_IUNIFORM_BUFFER_IMPL_H_

#include "renderer_backend.h"

namespace bebone::renderer {
    using namespace bebone::core;

    enum class UniformBufferHandle : u32 { Invalid = 0 };

    class IUniformBufferImpl : public NonCopyable {
        private:

        public:
            virtual ~IUniformBufferImpl() = default;

            virtual void upload_data(void* src, const size_t& size) = 0;
            virtual UniformBufferHandle get_handle() = 0;
    };

}

#endif
