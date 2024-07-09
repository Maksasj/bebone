#ifndef _BEBONE_RENDERER_RESOURCE_PLUG_H_
#define _BEBONE_RENDERER_RESOURCE_PLUG_H_

#include "iresource.h"

namespace bebone::renderer {
    class ResourcePlug {
        private:
            std::string name;
            std::shared_ptr<IResource>& resource;
            bool pluged_flag;

        public:
            ResourcePlug(const std::string& name, std::shared_ptr<IResource>& resource);

            void plug(const std::shared_ptr<IResource>& plug_resource);

            const std::string& get_name() const;
            const bool& is_plugged() const;
    };
}

#endif
