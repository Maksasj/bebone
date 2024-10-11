#ifndef _BEBONE_RENDERER_IMATERIAL_IMPL_H_
#define _BEBONE_RENDERER_IMATERIAL_IMPL_H_

#include "renderer_backend.h"
#include "itexture_impl.h"

namespace bebone::renderer {
    using namespace bebone::core;

    enum class MaterialHandle : u32 { Invalid = 0 };

    class IMaterialImpl : private NonCopyable {
        public:
            virtual ~IMaterialImpl() = default;

            virtual void set_properties(const void* properties) = 0;

            virtual MaterialHandle get_handle() const = 0;
    };
}

#endif
