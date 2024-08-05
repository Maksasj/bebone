#include "ipass_assembler.h"

namespace bebone::renderer {
    IPassAssembler::IPassAssembler(const std::shared_ptr<IProgramManager>& program_manager) : program_manager(program_manager) {

    }

    std::shared_ptr<IProgramManager> IPassAssembler::get_program_manager() const {
        return program_manager;
    }
}

