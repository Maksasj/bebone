#include "irender_graph_impl.h"

namespace bebone::renderer {
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
        render_resources.push_back(render_attachment);
    }

    std::optional<std::shared_ptr<IAttachment>> IRenderGraphImpl::get_render_attachment(const std::string& attachment_name) const {
        for(auto& attachment : render_resources)
            if(attachment->get_name() == attachment_name)
                return attachment;

        return std::nullopt;
    }

    std::vector<std::shared_ptr<IAttachment>>& IRenderGraphImpl::get_render_attachments() {
        return render_resources;
    }

    void IRenderGraphImpl::add_target(const std::shared_ptr<IRenderTarget> &render_target) {
        render_targets.push_back(render_target);
    }

    std::optional<std::shared_ptr<IRenderTarget>> IRenderGraphImpl::get_render_target(const std::string &render_target_name) const {
        for(auto& render_target : render_targets)
            if(render_target->get_name() == render_target_name)
                return render_target;

        return std::nullopt;
    }

    std::vector<std::shared_ptr<IRenderTarget>>& IRenderGraphImpl::get_render_targets() {
        return render_targets;
    }
}
