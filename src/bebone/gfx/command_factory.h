#ifndef _BEBONE_GFX_COMMAND_FACTORY_H_
#define _BEBONE_GFX_COMMAND_FACTORY_H_

#include "gfx_backend.h"

#include "commands.h"

namespace bebone::gfx {
    class CommandFactory {
        public:
            virtual Command begin_render_pass_command() const = 0;
    };
}

#endif
