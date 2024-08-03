#include "attachment_plug.h"

namespace bebone::renderer {
    AttachmentPlug::AttachmentPlug(const std::string& name, std::shared_ptr<IAttachment>& attachment) : name(name), attachment(attachment), pluged_flag(false) {

    }

    void AttachmentPlug::plug(const std::shared_ptr<IAttachment>& plug_attachment) {
        attachment = plug_attachment;
        pluged_flag = true;
    }

    const std::string& AttachmentPlug::get_name() const {
        return name;
    }

    const bool& AttachmentPlug::is_plugged() const {
        return pluged_flag;
    }
}
