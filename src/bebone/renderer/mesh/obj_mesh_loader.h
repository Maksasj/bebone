#ifndef _BEBONE_RENDERER_OBJ_MESH_LOADER_H_
#define _BEBONE_RENDERER_OBJ_MESH_LOADER_H_

#include "../renderer_backend.h"

#include "imesh_loader.h"

namespace bebone::renderer {
    class OBJMeshLoader : public IMeshLoader {
        public:
            OBJMeshLoader(const std::shared_ptr<IMeshBuilder>& builder);

            void reset() override;

            std::shared_ptr<IMesh> load_from_file(const std::string& file_path) override;
    };
}

#endif
