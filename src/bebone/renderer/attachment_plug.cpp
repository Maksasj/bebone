#include "attachment_plug.h"

namespace bebone::renderer {
    AttachmentPlug::AttachmentPlug(const std::string& name, std::shared_ptr<IAttachment>& resource) : name(name), resource(resource), pluged_flag(false) {

    }

    void AttachmentPlug::plug(const std::shared_ptr<IAttachment>& plug_attachment) {
        resource = plug_attachment;
        pluged_flag = true;
    }

    const std::string& AttachmentPlug::get_name() const {
        return name;
    }

    const bool& AttachmentPlug::is_plugged() const {
        return pluged_flag;
    }

    RenderTargetPlug::RenderTargetPlug(const std::string& name, std::shared_ptr<IRenderTarget>& resource) : name(name), resource(resource), pluged_flag(false) {

    }

    void RenderTargetPlug::plug(const std::shared_ptr<IRenderTarget>& plug_attachment) {
        resource = plug_attachment;
        pluged_flag = true;
    }

    const std::string& RenderTargetPlug::get_name() const {
        return name;
    }

    const bool& RenderTargetPlug::is_plugged() const {
        return pluged_flag;
    }
}
