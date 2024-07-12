#ifndef _BEBONE_RENDERER_IPROGRAM_H_
#define _BEBONE_RENDERER_IPROGRAM_H_

#include "icommand_encoder.h"

namespace bebone::renderer {
    class IProgram {
        public:
            virtual ~IProgram() = default;

            virtual void bind(ICommandEncoder* encoder) = 0;
    };
}

#endif
