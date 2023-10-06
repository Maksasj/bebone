#ifndef _WINDOW_FACTORY_H_
#define _WINDOW_FACTORY_H_

#include <memory>
#include <string>

#include "window.h"
#include "../gfx_api.h"

namespace bebone::gfx {
    class WindowFactory : private core::NonCopyable {
        public:
            static std::shared_ptr<Window> create_window(const std::string& title, const int width, const int height, const GfxAPI& gfxAPI);
    };
}

#endif
