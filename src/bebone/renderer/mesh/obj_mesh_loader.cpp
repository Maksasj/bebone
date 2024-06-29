#include "obj_mesh_loader.h"

namespace bebone::renderer {

    OBJMeshLoader::OBJMeshLoader(const std::shared_ptr<IMeshBuilder>& builder) : IMeshLoader(builder) {

    }

    std::shared_ptr<IMesh> OBJMeshLoader::load_from_file(const std::string& file) {

    }
}
