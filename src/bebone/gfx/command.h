#ifndef _BEBONE_GFX_COMMAND_H_
#define _BEBONE_GFX_COMMAND_H_

#include "../core/core.h"

#include "gfx_backend.h"

namespace bebone::gfx {
    struct Command {
        virtual void execute() = 0;
    };
}

#endif
