#ifndef _BEBONE_RENDERER_IMODEL_H_
#define _BEBONE_RENDERER_IMODEL_H_

#include "imaterial.h"
#include "imesh.h"

namespace bebone::renderer {
    using namespace bebone::core;

    class IModel {
        private:
            std::shared_ptr<IMesh> mesh;
            std::shared_ptr<IMaterial> material;

        public:
            IModel(const std::shared_ptr<IMesh>& mesh, const std::shared_ptr<IMaterial>& material);

            std::shared_ptr<IMesh> get_mesh() const;
            std::shared_ptr<IMaterial> get_material() const;

            virtual ~IModel() = default;
    };
}

#endif

