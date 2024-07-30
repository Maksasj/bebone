#ifndef _BEBONE_RENDERER_IMESH_MANAGER_H_
#define _BEBONE_RENDERER_IMESH_MANAGER_H_

#include "renderer_backend.h"
#include "mesh/imesh.h"

namespace bebone::renderer {
    using namespace bebone::core;

    class IMeshManager {
        public:
            virtual ~IMeshManager() = default;

            virtual MeshHandle load_mesh(const std::string& file_path) = 0;
            virtual MeshHandle create_mesh(const std::vector<Vertex>& vertices, const std::vector<u32>& indicies) = 0;

            virtual void draw_indexed(ICommandEncoder* encoder, const MeshHandle& handle) = 0;

            virtual std::optional<std::shared_ptr<IMesh>> get_mesh(const MeshHandle& handle) const = 0;
    };
}

#endif
