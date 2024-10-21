#include "icommand_encoder.h"

namespace bebone::renderer {
    using namespace bebone::core;

    ICommandEncoder::ICommandEncoder(const std::shared_ptr<IMeshManager>& mesh_manager) : mesh_manager(mesh_manager) {

    }

    std::shared_ptr<IMeshManager> ICommandEncoder::get_mesh_manager() const {
        return mesh_manager;
    }
}
