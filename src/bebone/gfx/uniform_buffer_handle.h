#ifndef _BEBONE_GFX_UNIFORM_BUFFER_HANDLE_H_
#define _BEBONE_GFX_UNIFORM_BUFFER_HANDLE_H_

namespace bebone::gfx {
    enum GPUResourceType {
        BEBONE_GPU_RESOURCE_TYPE_UNIFORM_BUFFER
    };

    struct UniformBufferHandle {
        const size_t index;
        const GPUResourceType type;

        UniformBufferHandle(const size_t& _index) : index(_index), type(BEBONE_GPU_RESOURCE_TYPE_UNIFORM_BUFFER) {
                
        }
    };
}

#endif
