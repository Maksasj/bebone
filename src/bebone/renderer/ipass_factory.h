#ifndef _BEBONE_RENDERER_IPASS_FACTORY_H_
#define _BEBONE_RENDERER_IPASS_FACTORY_H_

#include <string>

#include "ipass.h"
#include "ipresent_pass.h"
#include "irender_queue_pass.h"
#include "ideferred_g_pass.h"

namespace bebone::renderer {
    class IPassImplFactory {
        private:

        public:
            virtual ~IPassImplFactory() = default;

            virtual std::shared_ptr<IPassImpl> create_present_pass_impl() = 0;
            virtual std::shared_ptr<IPassImpl> create_deferred_g_pass_impl(const Vec2i& viewport) = 0;
    };
}

#endif
