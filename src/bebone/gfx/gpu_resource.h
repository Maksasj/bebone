#ifndef _BEBONE_GFX_RESOURCE_H_
#define _BEBONE_GFX_RESOURCE_H_

#include "uniform_buffer_handle.h"

namespace bebone::gfx {
    template<class GPUResourceHandleType>
    class GPUResource {
        private:
            GPUResourceHandleType handle;

        public:
            GPUResource(const GPUResourceHandleType& _handle) : handle(_handle) {
                
            }

            GPUResourceHandleType& get_handle() {
                return handle;
            }
    };
}

#endif
