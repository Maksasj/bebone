#ifndef _BEBONE_RENDERER_IDEPTH_RESOURCE_H_
#define _BEBONE_RENDERER_IDEPTH_RESOURCE_H_

#include "iresource.h"

namespace bebone::renderer {
    class IDepthResource : public IResource {
        private:

        public:
            IDepthResource(const std::string& name);
    };
}

#endif
