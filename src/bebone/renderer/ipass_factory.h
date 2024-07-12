#ifndef _BEBONE_RENDERER_IPASS_FACTORY_H_
#define _BEBONE_RENDERER_IPASS_FACTORY_H_

#include <string>

#include "ipass.h"
#include "ipresent_pass.h"
#include "irender_queue_pass.h"
#include "ideferred_g_pass.h"

namespace bebone::renderer {
    class IPassFactory {
        private:

        public:
            virtual ~IPassFactory() = default;

            virtual std::shared_ptr<IPresentPass> create_present_pass(const std::string& pass_name, const Vec2i& viewport) = 0;
            virtual std::shared_ptr<IDeferredGPass> create_deferred_g_pass(const std::string& pass_name, const Vec2i& viewport) = 0;
    };
}

#endif
