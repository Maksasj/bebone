#ifndef _BEBONE_RENDERER_IPASS_H_
#define _BEBONE_RENDERER_IPASS_H_

#include <string>

#include "renderer_backend.h"
#include "icommand_encoder.h"

namespace bebone::renderer {
    class IPass {
        private:
            std::string name;

        public:
            IPass(const std::string& name);
            virtual ~IPass() = default;

            virtual void record(ICommandEncoder* encoder) = 0;
            virtual void reset() = 0;

            const std::string& get_name() const;
    };
}

#endif
