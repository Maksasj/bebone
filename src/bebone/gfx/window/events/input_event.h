#ifndef _INPUT_EVENT_H_
#define _INPUT_EVENT_H_

#include "../../../core/core.h"

namespace bebone::gfx {
    using namespace bebone::core;

    /// Input events enumeration
    enum InputEvent {
        KEY,
        MOUSE_BUTTON
    };

    /// Key event structure
    struct InputKeyEvent : public Event<InputEvent, KEY> {
        i32 key;
        i32 scancode;
        i32 action;
        i32 mods;

        /*!
         * Default constructor
         * @param key - button key code
         * @param scancode - button scan code
         * @param action - event action
         * @param mods - button mod
        */
        InputKeyEvent(const i32& key, const i32& scancode, const i32& action, const i32& mods) : key(key), scancode(scancode), action(action), mods(mods) { }
    };

    /// Mouse button press event structure
    struct InputMouseButtonEvent : public Event<InputEvent, MOUSE_BUTTON> {
        i32 button;
        i32 action;
        i32 mods;

        /*!
         * Default constructor
         * @param button - mouse button key code
         * @param action - event action
         * @param mods - mouse button mod
        */
        InputMouseButtonEvent(const i32& button, const i32& action, const i32& mods) : button(button), action(action), mods(mods) { }
    };
}

#endif
