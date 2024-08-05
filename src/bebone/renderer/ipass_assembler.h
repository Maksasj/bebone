#ifndef _BEBONE_RENDERER_IPASS_ASSEMBLER_H_
#define _BEBONE_RENDERER_IPASS_ASSEMBLER_H_

#include "renderer_backend.h"
#include "iprogram_manager.h"

namespace bebone::renderer {
    class IPassAssembler {
        private:
            std::shared_ptr<IProgramManager> program_manager;

        public:
            IPassAssembler(const std::shared_ptr<IProgramManager>& program_manager);

            std::shared_ptr<IProgramManager> get_program_manager() const;
    };
}

#endif
