#ifndef _BEBONE_RENDERER_IPROGRAM_MANAGER_H_
#define _BEBONE_RENDERER_IPROGRAM_MANAGER_H_

#include "renderer_backend.h"
#include "vertex.h"
#include "icommand_encoder.h"

namespace bebone::renderer {
    class IProgramManager : public NonCopyable {
        public:
            virtual ~IProgramManager() = default;
    };
}

#endif
