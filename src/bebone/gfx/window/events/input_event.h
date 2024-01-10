#ifndef _INPUT_EVENT_H_
#define _INPUT_EVENT_H_

#include "../../../core/events/listeners/event.tpp"

namespace bebone::gfx {
    using namespace bebone::core;

    enum InputEvent {
        KEY,
        MOUSE_BUTTON
    };

    struct InputKeyEvent : public Event<InputEvent, KEY> {
        i32 key;
        i32 scancode;
        i32 action;
        i32 mods;

        InputKeyEvent(const i32& key, const i32& scancode, const i32& action, const i32& mods) : key(key), scancode(scancode), action(action), mods(mods) { }
    };

    struct InputMouseButtonEvent : public Event<InputEvent, MOUSE_BUTTON> {
        i32 button;
        i32 action;
        i32 mods;

        InputMouseButtonEvent(const i32& button, const i32& action, const i32& mods) : button(button), action(action), mods(mods) { }
    };
}

#endif
