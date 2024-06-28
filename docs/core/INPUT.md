# Input

## Input System
In Bebone you can use event-based input system to add some actions to your keys. Input class — is a singleton class, so you can get it's instance anywhere in your codebase.

Input system works with ```Action<>``` delegate. Because of this feature, you will subscribe/unsubscribe your keyboard keys and mouse buttons to the 'in-game actions' (such as jumping, running, etc.). You can do this with these two methods:
```c++
void register_key_action(const KeyCode& keyCode, std::function<void()>& action, const InputType& inputType = InputType::PRESS);
void remove_key_action(const KeyCode& keyCode, std::function<void()>& action, const InputType& inputType = InputType::PRESS);
```
* KeyCode — enum, which specifies the key to which you can subscribe an action
* action — 'in-game action'
* inputType — enum, which specifies in which case the action will be executed (by default it is set to PRESS)

All that is left to do is to add one command line inside the window loop to allow the framework to handle all the user input (maybe we will change it later):
```c++
window->execute_input_actions();
```

Example usage:
```с++
#include "bebone/bebone.h"

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

using namespace bebone::gfx;
using namespace bebone::gfx::opengl;

int main() {
    glfwInit();

    auto window = WindowFactory::create_window("0. Input example", SCR_WIDTH, SCR_HEIGHT, GfxAPI::OpenGL);

    GLContext::load_opengl();
    GLContext::set_viewport(0, 0, SCR_WIDTH, SCR_HEIGHT);

    // in-game action
    std::function<void()> keyPress = []() {
        std::cout << "key press\n";
    };

    // registering the key
    Input::get_instance().register_key_action(KeyCode::A, keyPress);

    while (!window->closing()) {
        GLContext::clear_color(0.2f, 0.2f, 0.2f, 1.0f);
        GLContext::clear(GL_COLOR_BUFFER_BIT);

        // without this your input will not work!
        window->execute_input_actions();

        glfwSwapBuffers(window->get_backend());
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
```