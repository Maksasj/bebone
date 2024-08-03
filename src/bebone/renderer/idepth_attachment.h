#ifndef _BEBONE_RENDERER_IDEPTH_ATTACHMENT_H_
#define _BEBONE_RENDERER_IDEPTH_ATTACHMENT_H_

#include "iattachment.h"

namespace bebone::renderer {
    class IDepthAttachment : public IAttachment {
        private:

        public:
            IDepthAttachment(const std::string& name);
    };
}

#endif
