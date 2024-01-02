#ifndef BEBONE_WINDOW_EVENT_H
#define BEBONE_WINDOW_EVENT_H

#include "../../../core/events/listeners/event.tpp"

namespace bebone::gfx {
    enum WindowEvent {
        WINDOW_POS,
        WINDOW_SIZE,
        WINDOW_CLOSE,
        WINDOW_REFRESH,
        WINDOW_FOCUS,
        WINDOW_ICONIFY,
        WINDOW_MAXIMIZE,
        FRAMEBUFFERS_SIZE,
        WINDOW_CONTENT_SCALE
    };

    struct WindowPosEvent : core::Event<WindowEvent, WINDOW_POS> {

    };

    struct WindowSizeEvent : core::Event<WindowEvent, WINDOW_SIZE> {

    };

    struct WindowCloseEvent : core::Event<WindowEvent, WINDOW_CLOSE> {

    };

    struct WindowRefreshEvent : core::Event<WindowEvent, WINDOW_REFRESH> {

    };

    struct WindowFocusEvent : core::Event<WindowEvent, WINDOW_FOCUS> {

    };

    struct WindowIconifyEvent : core::Event<WindowEvent, WINDOW_ICONIFY> {

    };

    struct WindowMaximizeEvent : core::Event<WindowEvent, WINDOW_MAXIMIZE> {

    };

    struct FrameBufferSizeEvent : core::Event<WindowEvent, FRAMEBUFFERS_SIZE> {

    };

    struct WindowContentScaleEvent : core::Event<WindowEvent, WINDOW_CONTENT_SCALE> {

    };
}

#endif
