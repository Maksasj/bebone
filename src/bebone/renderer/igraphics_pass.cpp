#include "igraphics_pass.h"

namespace bebone::renderer {
    IGraphicsPass::IGraphicsPass(
        const std::shared_ptr<IPassImpl>& impl,
        const std::string& name,
        const Vec2i& viewport
    ) : IPass(impl, name), program_set_flag(false), viewport(viewport) {

    }

    void IGraphicsPass::check_requirements() {
        if(!program_set_flag) {
            LOG_ERROR("IGraphicsPass is not provided with shader program");
            throw std::runtime_error("IGraphicsPass is not provided with shader program");
        }
    }

    void IGraphicsPass::set_program(const std::shared_ptr<IProgram>& arg_program) {
        this->program = arg_program;
        this->program_set_flag = true;
    }

    std::shared_ptr<IProgram> IGraphicsPass::get_program() const {
        return program;
    }

    void IGraphicsPass::set_camera(const std::shared_ptr<ICamera>& arg_camera) {
        this->camera = arg_camera;
        this->camera_set_flag = true;
    }

    std::shared_ptr<ICamera> IGraphicsPass::get_camera() const {
        return camera;
    }

    Vec2i IGraphicsPass::get_viewport() const {
        return viewport;
    }

    f32 IGraphicsPass::get_viewport_aspect_ratio() const {
        return static_cast<f32>(viewport.x) / static_cast<f32>(viewport.y);
    }
}