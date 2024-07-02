#ifndef _BEBONE_RENDERER_I_RENDERER_H_
#define _BEBONE_RENDERER_I_RENDERER_H_

#include "../gfx/gfx.h"

namespace bebone::renderer {
    class IRenderer {
        private:
            const GfxAPI api;

        public:
            IRenderer(const GfxAPI& api);

            virtual ~IRenderer() = default; 

    };
}

#endif
