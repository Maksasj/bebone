#ifndef _BEBONE_RENDERER_IMESH_H_
#define _BEBONE_RENDERER_IMESH_H_

#include "renderer_backend.h"
#include "vertex.h"
#include "icommand_encoder.h"

namespace bebone::renderer {
        class IMesh {
            public:
                virtual ~IMesh() = default;

                virtual void bind(ICommandEncoder* encoder) = 0;

                virtual u64 triangle_count() const = 0;
                virtual u64 vertex_count() const = 0;
        };
}

#endif
