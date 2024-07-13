#ifndef _BEBONE_RENDERER_IHDR_TEXTURE_RESOURCE_H_
#define _BEBONE_RENDERER_IHDR_TEXTURE_RESOURCE_H_

#include "iresource.h"

namespace bebone::renderer {
    class IHDRTextureResource : public IResource {
        private:

        public:
            IHDRTextureResource(const std::string& name);
    };
}

#endif
