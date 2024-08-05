#ifndef _BEBONE_RENDERER_IPROGRAM_MANAGER_H_
#define _BEBONE_RENDERER_IPROGRAM_MANAGER_H_

#include "renderer_backend.h"
#include "vertex.h"
#include "iprogram.h"
#include "ipass_impl.h"

namespace bebone::renderer {
    class IProgramManager : public NonCopyable {
        public:
            virtual ~IProgramManager() = default;

            virtual std::shared_ptr<IProgram> create_program(
                const std::shared_ptr<IPassImpl>& impl,
                const std::string& vertex_shader_code,
                const std::string& fragment_shader_code) = 0;
    };
}

#endif
