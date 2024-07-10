#ifndef _BEBONE_RENDERER_IRESOURCE_FACTORY_H_
#define _BEBONE_RENDERER_IRESOURCE_FACTORY_H_

#include <string>

#include "iresource.h"
#include "itexture_resource.h"
#include "idepth_resource.h"

namespace bebone::renderer {
    class IResourceFactory {
        private:

        public:
            virtual ~IResourceFactory() = default;

            virtual std::shared_ptr<ITextureResource> create_texture_resource(const std::string& pass_name) = 0;
            virtual std::shared_ptr<IDepthResource> create_depth_resource(const std::string& pass_name) = 0;
    };
}

#endif
