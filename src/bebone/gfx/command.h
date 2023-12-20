#ifndef _BEBONE_GFX_COMMAND_H_
#define _BEBONE_GFX_COMMAND_H_

namespace bebone::gfx {
    struct Command {
        virtual void execute() = 0;
    };
}

#endif
