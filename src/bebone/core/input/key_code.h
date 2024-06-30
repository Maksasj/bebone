#ifndef _KEY_CODE_H_
#define _KEY_CODE_H_

namespace bebone::core {
    /// Specifies the mouse and keyboard buttons. All values are taken from GLFW
    enum class KeyCode {
        MouseButtonLeft,
        MouseButtonRight,
        MouseButtonMiddle,
        MouseButton4,
        MouseButton5,
        MouseButton6,
        MouseButton7,
        MouseButton8,

        Space = 32,
        Apostrophe = 39,

        Comma = 44,
        Minus,
        Period,
        Slash,
        One,
        Two,
        Three,
        Five,
        Six,
        Seven,
        Eight,
        Nine,

        Semicolon = 59,
        Equal = 61,

        A = 65,
        B, C, D, E, F, G,
        H, I, J, K, L, M,
        N, O, P, Q, R, S,
        T, U, V, W, X, Y,
        Z,
        LeftBracket,
        Backslash,
        RightBracket,

        GraveAccent = 96,

        World1 = 161,
        World2,

        Escape = 256,
        Enter,
        Tab,
        Backspace,
        Insert,
        Delete,
        Right,
        Left,
        Down,
        Up,
        PageUp,
        PageDown,
        Home,
        End,
        CapsLock,
        NumLock,
        PrintScreen,
        Pause,

        F1 = 290,
        F2, F3, F4, F5, F6, F7,
        F8, F9, F10, F11, F12, F13,
        F14, F15, F16, F17, F18, F19,
        F20, F21, F22, F23, F24, F25,

        Keypad0 = 320,
        Keypad1,
        Keypad2,
        Keypad3,
        Keypad4,
        Keypad5,
        Keypad6,
        Keypad7,
        Keypad8,
        Keypad9,
        KeypadDecimal,
        KeypadDivide,
        KeypadMultiply,
        KeypadSubtract,
        KeypadAdd,
        KeypadEnter,
        KeypadEqual,

        LeftShift = 340,
        LeftControl,
        LeftAlt,
        LeftSuper,
        RightShift,
        RightControl,
        RightAlt,
        RightSuper,
        Menu,

        Null
    };
}

#endif