## Core module

### Action delegate(C# style)
Action delegate is a function object container which can subscribe to the specific functions or unsubscribe from them. Also, it can execute all functions to which action is subscribed. Action delegate can subscribe only to those functions who have void return type and some arguments (or without arguments) Action delegate is similar to the C# Action.

Example usage:
```c++
#include "bebone/bebone.h"

using namespace bebone::core;

void example_function(int x) {
    std::cout << "Example function: " << x << std::endl;
}

void another_function(int x) {
    std::cout << "Another Function: " << x + 40 << std::endl;
}

void meme(int x) {
    std::cout << "meme function" << x + 32445 / 23 << std::endl;
}

int main() {

    Action<int> action;
    std::function<void(int)> func = example_function;
    std::function<void(int)> func2 = another_function;
    std::function<void(int)> func3 = meme;

    action += func;
    action += func2;

    // subscribed functions: func, func2

    action(5);

    action -= func;
    action += func3;

    // subscribed functions: func2, func3

    action(4);

    action -= func2;

    // subscribed functions: func3

    action(0);

    action -= func3;

    // subscribed functions: none

    action(324);

    return 0;
}
```
In this example, ```Action``` can store function objects with one ```int``` argument. Overloaded operators:
* ```void operator+=(Function& function)``` — action subscribes to the function object
* ```void operator-=(Function& function)``` — action unsubscribes from the function object
* ```void operator()(Args... args)``` — action executes all functions to which it subscribed

### Event system (Java style)
Bebone supports java style event system, there is three basic classes
* **Event**<br> 
  Base class for all events. Lets create simple event, firstly we need to create event category enum:
  ```c++
  enum SomeEventCategory {
    COOL_EVENT,
    NOT_COOL_EVENT
  }
  ```
  Next, lets create two event classes for each event type:
  ```c++
  struct CoolEvent : public Event<SomeEventCategory, COOL_EVENT> {};
  struct NotCoolEvent : public Event<SomeEventCategory, NOT_COOL_EVENT> {};
  ```
  Note, that event can have it own methods or member variables. After event class declaration you can easelly use in **EventListener** or **EventDispatcher**.
* **EventListener**<br>
  Next, let's take a look at event listeneres. It is very easy to create your own event listeren, you just need dervice a class from 
  EventListener class using your desired event type as template argument.
  ```c++
  struct CoolEventListener : EventListener<CoolEvent> {
    void operator()(CoolEvent&) {
        std::cout << "Yea cool event !";
    }
  };
  ```
  Note that not only event listener class object can be used as listener, but also a c++ style lambda and regular functions.
* **EventDispatcher**<br>
  Last but not least, EventDispatcher class. This class stores list of all added listeners and sends fired event to needed listeners. Lets take a look:
  ```c++
  EventDispatcher<SomeEventCategory> dispatcher;

  dispatcher.add_listener([](CoolEvent&) {
    std::cout << "This is cool event";
  });
  dispatcher.add_listener([](NotCoolEvent&) {
    std::cout << "This is not cool event";
  });
  ```
  As you see, in this example we added two listeners to our dispatcher. One that listens for **CoolEvent**, and one that listens for **NotCoolEvent**.

  After you can simply fire desired event:
  ```c++
  dispatcher.fire(CoolEvent());
  dispatcher.fire(NotCoolEvent());
  ```

  Dispatcher after receiving an event will automatically send it to listeners that are listening specifically for **THIS** event type. As a result we will get:

  ```bash
  This is cool event
  This is not cool event
  ```

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

    auto window = WindowFactory::create_window("0. Input example", SCR_WIDTH, SCR_HEIGHT, GfxAPI::OPENGL);

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