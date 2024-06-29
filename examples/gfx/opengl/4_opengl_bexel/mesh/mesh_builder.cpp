#include "mesh_builder.h"

namespace bexel {
    MeshBuilder::MeshBuilder() : index_offset(0) {

    }

    unique_ptr<Mesh> MeshBuilder::build() {
        return make_unique<Mesh>(vertices, indices);
    }
}