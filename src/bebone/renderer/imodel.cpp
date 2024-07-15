#include "imodel.h"

namespace bebone::renderer {
    using namespace bebone::core;

    IModel::IModel(const std::shared_ptr<IMesh>& mesh, const std::shared_ptr<IMaterial>& material) : mesh(mesh), material(material) {

    }

    std::shared_ptr<IMesh> IModel::get_mesh() const {
        return mesh;
    }

    std::shared_ptr<IMaterial> IModel::get_material() const {
        return material;
    }
}
