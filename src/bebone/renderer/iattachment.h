#ifndef _BEBONE_RENDERER_IATTACHMENT_H_
#define _BEBONE_RENDERER_IATTACHMENT_H_

#include <string>

#include "renderer_backend.h"
#include "icommand_encoder.h"

namespace bebone::renderer {
    class IAttachment : public NonCopyable {
        private:
            std::string name;

        public:
            IAttachment(const std::string& name);
            virtual ~IAttachment() = default;

            [[nodiscard]] const std::string& get_name() const;
    };
}

#endif
