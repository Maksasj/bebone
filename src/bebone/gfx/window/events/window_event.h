#ifndef BEBONE_WINDOW_EVENT_H
#define BEBONE_WINDOW_EVENT_H

#include "../../../core/core.h"

namespace bebone::gfx {
    using namespace bebone::core;

    /// Window events enumeration
    enum WindowEvent {
        WindowPos,
        WindowSize,
        WindowClose,
        WindowRefresh,
        WindowFocus,
        WindowIconify,
        WindowMaximize,
        FramebuffersSize,
        WindowContentScale
    };

    /// Window position change event structure
    struct WindowPosEvent : public Event<WindowEvent, WindowPos> {
        i32 x_pos;
        i32 y_pos;

        /*!
         * Default constructor
         * @param x_pos - new window x position
         * @param y_pos - new window y position
        */
        WindowPosEvent(const i32& x_pos, const i32& y_pos) : x_pos(x_pos), y_pos(y_pos) {}
    };

    /// Window size change event structure
    struct WindowSizeEvent : public Event<WindowEvent, WindowSize> {
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
    struct WindowCloseEvent : public Event<WindowEvent, WindowClose> {

    };

    /// Window refresh event structure
    struct WindowRefreshEvent : public Event<WindowEvent, WindowRefresh> {

    };

    /// Window focus event structure
    struct WindowFocusEvent : public Event<WindowEvent, WindowFocus> {
        i32 focused;

        /*!
         * Default constructor
         * @param focused - new window focus value
        */
        WindowFocusEvent(const i32& focused) : focused(focused) {}
    };

    /// Window iconify event structure
    struct WindowIconifyEvent : public Event<WindowEvent, WindowIconify> {
        i32 iconified;

        /*!
         * Default constructor
         * @param iconified - new window iconified value
        */
        WindowIconifyEvent(const i32& iconified) : iconified(iconified) {}
    };

    /// Window maximize event structure
    struct WindowMaximizeEvent : public Event<WindowEvent, WindowMaximize> {
        i32 maximized;

        /*!
         * Default constructor
         * @param maximized - new window maximized value
        */
        WindowMaximizeEvent(const i32& maximized) : maximized(maximized) {}
    };

    /// Window framebuffer size change event structure
    struct FrameBufferSizeEvent : public Event<WindowEvent, FramebuffersSize> {
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
    struct WindowContentScaleEvent : public Event<WindowEvent, WindowContentScale> {
        f32 x_scale;
        f32 y_scale;

        /*!
         * Default constructor
         * @param x_scale - new window x content scale
         * @param y_scale - new window y content scale
        */
        WindowContentScaleEvent(const f32& x_scale, const f32& y_scale) : x_scale(x_scale), y_scale(y_scale) {}
    };
}

#endif
