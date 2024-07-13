#include "irender_queue_pass.h"

namespace bebone::renderer {
    IRenderQueuePass::IRenderQueuePass(
        const std::string& pass_name,
        const Vec2i& viewport
    ) : IGraphicsPass(pass_name, viewport) {

    }
}
