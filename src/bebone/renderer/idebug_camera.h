#ifndef _BEBONE_RENDERER_IDEBUG_CAMERA_H_
#define _BEBONE_RENDERER_IDEBUG_CAMERA_H_

#include "iperspective_camera.h"

namespace bebone::renderer {
    using namespace bebone::gfx;

    class IDebugCamera : public IPerspectiveCamera {
        private:
            std::shared_ptr<InputExecutor> input;

        public:
            IDebugCamera(std::shared_ptr<Window>& window);
    };
}

#endif
