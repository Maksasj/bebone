#include "igraphics_pass.h"

namespace bebone::renderer {
    IGraphicsPass::IGraphicsPass(
        const std::string& name,
        const Vec2i& viewport
    ) : IPass(name), program_set_flag(false), viewport(viewport) {

    }

    void IGraphicsPass::check_requirements() {
        if(!program_set_flag)
            throw std::runtime_error("IGraphicsPass is not provided with shader program");
    }

    void IGraphicsPass::set_program(const std::shared_ptr<IProgram>& arg_program) {
        this->program = arg_program;
        this->program_set_flag = true;
    }

    std::shared_ptr<IProgram> IGraphicsPass::get_program() const {
        return program;
    }

    const Vec2i& IGraphicsPass::get_viewport() const {
        return viewport;
    }
}