#include "irender_graph_impl.h"

namespace bebone::renderer {
    IRenderGraphImpl::IRenderGraphImpl() {

    }

    void IRenderGraphImpl::add_pass(const std::shared_ptr<IPass>& render_pass) {
        render_passes.push_back(render_pass);
    }

    std::optional<std::shared_ptr<IPass>> IRenderGraphImpl::get_render_pass(const std::string& pass_name) const {
        for(auto& pass : render_passes)
            if(pass->get_name() == pass_name)
                return pass;

        return std::nullopt;
    }

    std::vector<std::shared_ptr<IPass>>& IRenderGraphImpl::get_render_passes() {
        return render_passes;
    }

    void IRenderGraphImpl::add_attachment(const std::shared_ptr<IAttachment>& render_attachment) {
        render_attachments.push_back(render_attachment);
    }

    std::optional<std::shared_ptr<IAttachment>> IRenderGraphImpl::get_render_attachment(const std::string& attachment_name) const {
        for(auto& attachment : render_attachments)
            if(attachment->get_name() == attachment_name)
                return attachment;

        return std::nullopt;
    }

    std::vector<std::shared_ptr<IAttachment>>& IRenderGraphImpl::get_render_attachments() {
        return render_attachments;
    }
}
