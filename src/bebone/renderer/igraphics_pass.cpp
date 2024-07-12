#include "igraphics_pass.h"

namespace bebone::renderer {
    IGraphicsPass::IGraphicsPass(const std::string& name) : IPass(name) {

    }

    void IGraphicsPass::set_program(const std::shared_ptr<IProgram>& arg_program) {
        this->program = arg_program;
    }

    std::shared_ptr<IProgram> IGraphicsPass::get_program() const {
        return program;
    }

    const Vec2i& IGraphicsPass::get_viewport() const {
        return viewport;
    }
}