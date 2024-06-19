#ifndef BEBONE_WINDOW_EVENT_H
#define BEBONE_WINDOW_EVENT_H

#include "../../../core/core.h"

namespace bebone::gfx {
    using namespace bebone::core;

    /// Window events enumeration
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

    /// Window position change event structure
    struct WindowPosEvent : public Event<WindowEvent, WINDOW_POS> {
        i32 xPos;
        i32 yPos;

        /*!
         * Default constructor
         * @param xPos - new window x position
         * @param yPos - new window y position
        */
        WindowPosEvent(const i32& xPos, const i32& yPos) : xPos(xPos), yPos(yPos) {}
    };

    /// Window size change event structure
    struct WindowSizeEvent : public Event<WindowEvent, WINDOW_SIZE> {
        i32 width;
        i32 height;

        /*!
         * Default constructor
         * @param width - new window width
         * @param height - new window height
        */
        WindowSizeEvent(const i32& width, const i32& height) : width(width), height(height) {}
    };

    /// Window close event structure
    struct WindowCloseEvent : public Event<WindowEvent, WINDOW_CLOSE> {

    };

    /// Window refresh event structure
    struct WindowRefreshEvent : public Event<WindowEvent, WINDOW_REFRESH> {

    };

    /// Window focus event structure
    struct WindowFocusEvent : public Event<WindowEvent, WINDOW_FOCUS> {
        i32 focused;

        /*!
         * Default constructor
         * @param focused - new window focus value
        */
        WindowFocusEvent(const i32& focused) : focused(focused) {}
    };

    /// Window iconify event structure
    struct WindowIconifyEvent : public Event<WindowEvent, WINDOW_ICONIFY> {
        i32 iconified;

        /*!
         * Default constructor
         * @param iconified - new window iconified value
        */
        WindowIconifyEvent(const i32& iconified) : iconified(iconified) {}
    };

    /// Window maximize event structure
    struct WindowMaximizeEvent : public Event<WindowEvent, WINDOW_MAXIMIZE> {
        i32 maximized;

        /*!
         * Default constructor
         * @param maximized - new window maximized value
        */
        WindowMaximizeEvent(const i32& maximized) : maximized(maximized) {}
    };

    /// Window framebuffer size change event structure
    struct FrameBufferSizeEvent : public Event<WindowEvent, FRAMEBUFFERS_SIZE> {
        i32 width;
        i32 height;

        /*!
         * Default constructor
         * @param width - new window frame buffer width
         * @param height - new window frame buffer height
        */
        FrameBufferSizeEvent(const i32& width, const i32& height) : width(width), height(height) {}
    };

    /// Window content scale change event structure
    struct WindowContentScaleEvent : public Event<WindowEvent, WINDOW_CONTENT_SCALE> {
        f32 xScale;
        f32 yScale;

        /*!
         * Default constructor
         * @param xScale - new window x content scale
         * @param yScale - new window y content scale
        */
        WindowContentScaleEvent(const f32& xScale, const f32& yScale) : xScale(xScale), yScale(yScale) {}
    };
}

#endif
