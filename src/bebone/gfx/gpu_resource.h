#ifndef _BEBONE_GFX_RESOURCE_H_
#define _BEBONE_GFX_RESOURCE_H_

#include "resource_handle.h"

namespace bebone::gfx {
    class GPUResource {
        private:
            const GPUResourceHandle handle;

        public:
            GPUResource(const GPUResourceHandle& _handle) : handle(_handle) {
                
            }

            const GPUResourceHandle& get_handle() const {
                return handle;
            }
    };
}

#endif
