#ifndef _BEBONE_GFX_WINDOW_WINDOW_FACTORY_H_
#define _BEBONE_GFX_WINDOW_WINDOW_FACTORY_H_

#include <memory>
#include <string>

#include "window.h"
#include "../gfx_api.h"

namespace bebone::gfx {
    /// This class is used to create a window
    class WindowFactory : private core::NonCopyable {
        public:
            /*!
             * Creates a window object with specified title, resolution and graphics api
             * @param title - window name/title
             * @param width - window width
             * @param height - window height
             * @param gfx_api - graphics API
             *
             * @return Window object
            */
            static std::shared_ptr<Window> create_window(const std::string& title, const int& width, const int& height, const GfxAPI& gfx_api, const WindowProperties& properties = {});
    };
}

#endif
