#ifndef _BEBONE_RENDERER_IRENDER_TARGET_H_
#define _BEBONE_RENDERER_IRENDER_TARGET_H_

#include "renderer_backend.h"
#include "irender_target_impl.h"

namespace bebone::renderer {
    using namespace bebone::core;

    class IRenderTarget {
        private:
            std::shared_ptr<IRenderTargetImpl> impl;
            std::string name;

        public:
            IRenderTarget(const std::shared_ptr<IRenderTargetImpl>& impl, std::string  name);

            [[nodiscard]] std::shared_ptr<IRenderTargetImpl> get_impl() const;
            [[nodiscard]] std::string get_name() const;
    };
}

#endif
