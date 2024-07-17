#ifndef _BEBONE_RENDERER_IRESOURCE_FACTORY_H_
#define _BEBONE_RENDERER_IRESOURCE_FACTORY_H_

#include <string>

#include "iresource.h"

#include "itexture_resource.h"
#include "ihdr_texture_resource.h"
#include "idepth_resource.h"

namespace bebone::renderer {
    using namespace bebone::gfx;

    class IResourceFactory {
        private:

        public:
            virtual ~IResourceFactory() = default;

            virtual std::shared_ptr<ITextureResource> create_texture_resource(const std::string& pass_name, const Vec2i& size) = 0;
            virtual std::shared_ptr<IHDRTextureResource> create_hdr_texture_resource(const std::string& pass_name, const Vec2i& size) = 0;
            virtual std::shared_ptr<IDepthResource> create_depth_resource(const std::string& pass_name, const Vec2i& size) = 0;
    };
}

#endif