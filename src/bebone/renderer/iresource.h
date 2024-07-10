#ifndef _BEBONE_RENDERER_IRESOURCE_H_
#define _BEBONE_RENDERER_IRESOURCE_H_

#include <string>

#include "renderer_backend.h"
#include "icommand_encoder.h"

namespace bebone::renderer {
    class IResource {
        private:
            std::string name;

        public:
            IResource(const std::string& name);
            virtual ~IResource() = default;

            const std::string& get_name() const;
    };
}

#endif
