#include "ipass.h"

namespace bebone::renderer {
    void IPass::register_input(const std::string& attachment_name, std::shared_ptr<IAttachment>& attachment) {
        // Check if plug with same name does not exist
        inputs.emplace_back(attachment_name, attachment);
    }

    void IPass::register_output(const std::string& attachment_name, std::shared_ptr<IAttachment>& attachment) {
        // Check if plug with same name does not exist
        outputs.emplace_back(attachment_name, attachment);
    }

    IPass::IPass(const std::string& name) : name(name) {

    }

    std::string IPass::get_name() const {
        return name;
    }

    void IPass::plug_input(const std::string& attachment_name, const std::shared_ptr<IAttachment>& attachment) {
        for(auto& plug : inputs) {
            if(plug.get_name() != attachment_name)
                continue;

            plug.plug(attachment);
            break;
        }
    }

    void IPass::plug_output(const std::string& attachment_name, const std::shared_ptr<IAttachment>& attachment) {
        for(auto& plug : outputs) {
            if(plug.get_name() != attachment_name)
                continue;

            plug.plug(attachment);
            break;
        }
    }
}
