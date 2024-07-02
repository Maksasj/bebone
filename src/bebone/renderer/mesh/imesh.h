#ifndef _BEBONE_RENDERER_IMESH_H_
#define _BEBONE_RENDERER_IMESH_H_

#include "../renderer_backend.h"
#include "../vertex.h"
#include "../ibindable.h"

namespace bebone::renderer {
        // Todo, probably need to inherit from some sort of Bindable,
        // and maybe should have child's like IVertexMesh and ITriangleMesh ?
        class IMesh : public IBindable {
            private:

            public:
                virtual ~IMesh() = default;

                virtual u64 triangle_count() const = 0;
                virtual u64 vertex_count() const = 0;
        };
}

#endif
