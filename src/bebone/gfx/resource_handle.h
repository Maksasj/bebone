#ifndef _BEBONE_GFX_RESOURCE_HANDLE_H_
#define _BEBONE_GFX_RESOURCE_HANDLE_H_

namespace bebone::gfx {
    enum GPUResourceType {
        BEBONE_GPU_RESOURCE_TYPE_UNIFORM_BUFFER
    };

    struct GPUResourceHandle {
        private:
            GPUResourceHandle(const size_t& _index, const GPUResourceType& _type) : index(_index), type(_type) {

            }

        public:

        const size_t index;
        const GPUResourceType type;

        static GPUResourceHandle uniform(const size_t& index) {
            return GPUResourceHandle(index, BEBONE_GPU_RESOURCE_TYPE_UNIFORM_BUFFER);
        }
    };
}

#endif
