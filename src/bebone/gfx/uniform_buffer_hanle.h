#ifndef _BEBONE_GFX_UNIFORM_BUFFER_HANDLE_H_
#define _BEBONE_GFX_UNIFORM_BUFFER_HANDLE_H_

#include "resource_handle.h"

namespace bebone::gfx {
    struct UniformBufferHandle : GPUResourceHandle{
        UniformBufferHandle(const size_t& _index) : GPUResourceHandle(_index, BEBONE_GPU_RESOURCE_TYPE_UNIFORM_BUFFER) {

        }
    };
}

#endif
