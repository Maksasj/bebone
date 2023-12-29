#include "bebone/bebone.h"

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

using namespace bebone::gfx;
using namespace bebone::gfx::opengl;

/*
 * This will not compile

  class NotEvent {

  };

  class BadEventListener : EventListener<NotEvent> {
  public:
      void handle_event(shared_ptr<NotEvent> event) override { }
  };
*/

int main() {
    glfwInit();
    
    auto window = WindowFactory::create_window("0. Event Listener example", SCR_WIDTH, SCR_HEIGHT, GfxAPI::OPENGL);

    GLContext::load_opengl();
    GLContext::set_viewport(0, 0, SCR_WIDTH, SCR_HEIGHT);

    while (!window->closing()) {
        GLContext::clear_color(0.2f, 0.2f, 0.2f, 1.0f);
        GLContext::clear(GL_COLOR_BUFFER_BIT);

        glfwSwapBuffers(window->get_backend());
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
