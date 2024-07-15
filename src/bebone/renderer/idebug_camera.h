#ifndef _BEBONE_RENDERER_IDEBUG_CAMERA_H_
#define _BEBONE_RENDERER_IDEBUG_CAMERA_H_

#include "iperspective_camera.h"

namespace bebone::renderer {
    using namespace bebone::gfx;

    class IDebugCamera : public IPerspectiveCamera {
        private:
            std::shared_ptr<Window> window;
            f32 speed;
            bool mouse_locked;

        protected:
            void update_debug_camera();

            void update_camera_rotation();
            void update_camera_position();
            void handle_mouse_lock(shared_ptr<Window>& window);

        public:
            IDebugCamera(const std::shared_ptr<Window>& window);

    };
}

#endif
