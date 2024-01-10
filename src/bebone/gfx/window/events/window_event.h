#ifndef BEBONE_WINDOW_EVENT_H
#define BEBONE_WINDOW_EVENT_H

#include "../../../core/events/listeners/event.tpp"

namespace bebone::gfx {
    using namespace bebone::core;

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

    struct WindowPosEvent : public Event<WindowEvent, WINDOW_POS> {
        i32 xPos;
        i32 yPos;

        WindowPosEvent(const i32& xPos, const i32& yPos) : xPos(xPos), yPos(yPos) {}
    };

    struct WindowSizeEvent : public Event<WindowEvent, WINDOW_SIZE> {
        i32 width;
        i32 height;

        WindowSizeEvent(const i32& width, const i32& height) : width(width), height(height) {}
    };

    struct WindowCloseEvent : public Event<WindowEvent, WINDOW_CLOSE> {

    };

    struct WindowRefreshEvent : public Event<WindowEvent, WINDOW_REFRESH> {

    };

    struct WindowFocusEvent : public Event<WindowEvent, WINDOW_FOCUS> {
        i32 focused;

        WindowFocusEvent(const i32& focused) : focused(focused) {}
    };

    struct WindowIconifyEvent : public Event<WindowEvent, WINDOW_ICONIFY> {
        i32 iconified;

        WindowIconifyEvent(const i32& iconified) : iconified(iconified) {}
    };

    struct WindowMaximizeEvent : public Event<WindowEvent, WINDOW_MAXIMIZE> {
        i32 maximized;

        WindowMaximizeEvent(const i32& maximized) : maximized(maximized) {}
    };

    struct FrameBufferSizeEvent : public Event<WindowEvent, FRAMEBUFFERS_SIZE> {
        i32 width;
        i32 height;

        FrameBufferSizeEvent(const i32& width, const i32& height) : width(width), height(height) {}
    };

    struct WindowContentScaleEvent : public Event<WindowEvent, WINDOW_CONTENT_SCALE> {
        f32 xScale;
        f32 yScale;

        WindowContentScaleEvent(const f32& xScale, const f32& yScale) : xScale(xScale), yScale(yScale) {}
    };
}

#endif
