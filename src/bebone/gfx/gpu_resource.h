#ifndef _BEBONE_GFX_RESOURCE_H_
#define _BEBONE_GFX_RESOURCE_H_

#include "uniform_buffer_handle.h"

namespace bebone::gfx {
    template<class GPUResourceHandleType>
    class GPUResource {
        private:
            const GPUResourceHandleType handle;

        public:
            GPUResource(const GPUResourceHandleType& _handle) : handle(_handle) {
                
            }

            const GPUResourceHandleType& get_handle() const {
                return handle;
            }
    };
}

#endif
