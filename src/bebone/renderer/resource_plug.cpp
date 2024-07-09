#include "resource_plug.h"

namespace bebone::renderer {
    ResourcePlug::ResourcePlug(const std::string& name, std::shared_ptr<IResource>& resource) : name(name), resource(resource), pluged_flag(false) {

    }

    void ResourcePlug::plug(const std::shared_ptr<IResource>& plug_resource) {
        resource = plug_resource;
        pluged_flag = true;
    }

    const std::string& ResourcePlug::get_name() const {
        return name;
    }

    const bool& ResourcePlug::is_plugged() const {
        return pluged_flag;
    }
}
