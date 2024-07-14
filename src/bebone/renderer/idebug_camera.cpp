#include "idebug_camera.h"

namespace bebone::renderer {
    using namespace bebone::gfx;

    IDebugCamera::IDebugCamera(std::shared_ptr<Window>& window) : IPerspectiveCamera() {
        input = std::make_shared<InputExecutor>(std::make_shared<Input>());

        window->add_listener([&](WindowPullEventsEvent& event) {
            std::cout << "refresh \n";
        });
    }
}
