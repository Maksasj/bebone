#ifndef _BEBONE_RENDERER_IPASS_FACTORY_H_
#define _BEBONE_RENDERER_IPASS_FACTORY_H_

#include <string>

#include "renderer_backend.h"
#include "ipass.h"

namespace bebone::renderer {
    class IPassFactory {
        private:

        public:
            virtual ~IPassFactory() = default;

            virtual std::shared_ptr<IPresentPass> create_present_pass(const std::string& pass_name) = 0;
            virtual std::shared_ptr<IGeometryPass> create_geometry_pass(const std::string& pass_name) = 0;
    };
}

#endif
