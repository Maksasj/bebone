#ifndef _BEBONE_RENDERER_ITEXTURE_RESOURCE_H_
#define _BEBONE_RENDERER_ITEXTURE_RESOURCE_H_

#include "iresource.h"

namespace bebone::renderer {
    class ITextureResource : public IResource {
        private:

        public:
            ITextureResource(const std::string& name);
    };
}

#endif
