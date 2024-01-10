#ifndef _KEY_CODE_H_
#define _KEY_CODE_H_

namespace bebone::core {
    /// Specifies the mouse and keyboard buttons. All values are taken from GLFW
    enum KeyCode {
        MOUSE_BUTTON_LEFT,
        MOUSE_BUTTON_RIGHT,
        MOUSE_BUTTON_MIDDLE,
        MOUSE_BUTTON_4,
        MOUSE_BUTTON_5,
        MOUSE_BUTTON_6,
        MOUSE_BUTTON_7,
        MOUSE_BUTTON_8,

        SPACE = 32,
        APOSTROPHE = 39,

        COMMA = 44,
        MINUS,
        PERIOD,
        SLASH,
        ONE,
        TWO,
        THREE,
        FIVE,
        SIX,
        SEVEN,
        EIGHT,
        NINE,

        SEMICOLON = 59,
        EQUAL = 61,

        A = 65,
        B, C, D, E, F, G,
        H, I, J, K, L, M,
        N, O, P, Q, R, S,
        T, U, V, W, X, Y,
        Z,
        LEFT_BRACKET,
        BACKSLASH,
        RIGHT_BRACKET,

        GRAVE_ACCENT = 96,

        WORLD_1 = 161,
        WORLD_2,

        ESCAPE = 256,
        ENTER,
        TAB,
        BACKSPACE,
        INSERT,
        DELETE,
        RIGHT,
        LEFT,
        DOWN,
        UP,
        PAGE_UP,
        PAGE_DOWN,
        HOME,
        END,
        CAPS_LOCK,
        NUM_LOCK,
        PRINT_SCREEN,
        PAUSE,

        F1 = 290,
        F2, F3, F4, F5, F6, F7,
        F8, F9, F10, F11, F12, F13,
        F14, F15, F16, F17, F18, F19,
        F20, F21, F22, F23, F24, F25,

        KEYPAD_0 = 320,
        KEYPAD_1,
        KEYPAD_2,
        KEYPAD_3,
        KEYPAD_4,
        KEYPAD_5,
        KEYPAD_6,
        KEYPAD_7,
        KEYPAD_8,
        KEYPAD_9,
        KEYPAD_DECIMAL,
        KEYPAD_DIVIDE,
        KEYPAD_MULTIPLY,
        KEYPAD_SUBTRACT,
        KEYPAD_ADD,
        KEYPAD_ENTER,
        KEYPAD_EQUAL,

        LEFT_SHIFT = 340,
        LEFT_CONTROL,
        LEFT_ALT,
        LEFT_SUPER,
        RIGHT_SHIFT,
        RIGHT_CONTROL,
        RIGHT_ALT,
        RIGHT_SUPER,
        MENU
    };
}

#endif