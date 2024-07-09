#include "ipass.h"

namespace bebone::renderer {
    void IPass::register_input(const std::string& resource_name, std::shared_ptr<IResource>& resource) {
        // Check if plug with same name does not exist
        inputs.emplace_back(resource_name, resource);
    }

    void IPass::register_output(const std::string& resource_name, std::shared_ptr<IResource>& resource) {
        // Check if plug with same name does not exist
        outputs.emplace_back(resource_name, resource);
    }

    IPass::IPass(const std::string& name) : name(name) {

    }

    const std::string& IPass::get_name() const {
        return name;
    }

    void IPass::plug_input(const std::string& resource_name, const std::shared_ptr<IResource>& resource) {
        for(auto& plug : inputs) {
            if(plug.get_name() != resource_name)
                continue;

            plug.plug(resource);
            break;
        }
    }

    void IPass::plug_output(const std::string& resource_name, const std::shared_ptr<IResource>& resource) {
        for(auto& plug : outputs) {
            if(plug.get_name() != resource_name)
                continue;

            plug.plug(resource);
            break;
        }
    }
}
