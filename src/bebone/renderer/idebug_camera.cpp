#include "idebug_camera.h"

namespace bebone::renderer {
    using namespace bebone::gfx;

    IDebugCamera::IDebugCamera(std::shared_ptr<Window>& window) : IPerspectiveCamera() {
        window->add_listener([&](InputKeyEvent& event) {
            if(event.key == KeyCode::S) {
                apply_position({0, 0, 0.4});
            } else if(event.key == KeyCode::W) {
                apply_position({0, 0, -0.4});
            }
        });
    }
}
