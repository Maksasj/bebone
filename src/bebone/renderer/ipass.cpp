#include "ipass.h"

#include <utility>

namespace bebone::renderer {
    void IPass::register_resource(const std::string& name, std::shared_ptr<IAttachment>& attachment) {
        // Check if plug with same name does not exist
        attachment_resources.emplace_back(name, attachment);
    }

    void IPass::register_resource(const std::string& name, std::shared_ptr<IRenderTarget>& render_target) {
        render_target_resources.emplace_back(name, render_target);
    }

    IPass::IPass(const std::shared_ptr<IPassImpl>& impl, std::string  name) : impl(impl), name(std::move(name)) {

    }

    std::string IPass::get_name() const {
        return name;
    }

    void IPass::set_impl(const std::shared_ptr<IPassImpl>& new_impl) {
        impl = new_impl;
    }

    std::shared_ptr<IPassImpl> IPass::get_impl() const {
        return impl;
    }

    void IPass::assemble(std::shared_ptr<IPassAssembler>& assember) {
        std::ignore = assember;
    }

    void IPass::check_requirements() {

    }

    void IPass::record(ICommandEncoder* encoder) {
        std::ignore = encoder;
    }

    void IPass::reset() {

    }

    void IPass::resize_viewport(const Vec2i& new_size) {
        std::ignore = new_size;
    }

    void IPass::plug(const std::string& name, const std::shared_ptr<IAttachment>& attachment) {
        for(auto& plug : attachment_resources) {
            if(plug.get_name() != name)
                continue;

            plug.plug(attachment);
            break;
        }
    }

    void IPass::plug(const std::string& name, const std::shared_ptr<IRenderTarget>& render_target) {
        for(auto& plug : render_target_resources) {
            if(plug.get_name() != name)
                continue;

            plug.plug(render_target);
            break;
        }
    }
}
