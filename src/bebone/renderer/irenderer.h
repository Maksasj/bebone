#ifndef _BEBONE_RENDERER_IRENDERER_H_
#define _BEBONE_RENDERER_IRENDERER_H_

#include "renderer_backend.h"

#include "irender_graph.h"
#include "ipass.h"

#include "itexture_impl.h"

#include "imaterial.h"
#include "imaterial_impl.h"

#include "mesh/imesh_impl.h"
#include "mesh/imesh_builder.h"
#include "mesh/imesh_generator.h"
#include "mesh/imesh_loader.h"
#include "mesh/obj_mesh_loader.h"

#include "vertex.h"
#include "transform.h"

#include "pbr_render_graph.h"

#include "iprogram_manager.h"
#include "itexture_manager.h"
#include "imesh_manager.h"
#include "imaterial_manager.h"

namespace bebone::renderer {
    class IRenderer : public NonCopyable {
        protected:
            virtual void resize_viewport(const Vec2i& new_size) = 0;

            std::shared_ptr<IRenderGraph> create_default_render_graph(const Vec2i& viewport);
            virtual std::shared_ptr<IRenderGraphImpl> create_render_graph_impl() = 0;

        public:
            virtual ~IRenderer() = default;

            // Managers
            [[nodiscard]] virtual std::shared_ptr<IProgramManager> get_program_manager() const = 0;
            [[nodiscard]] virtual std::shared_ptr<ITextureManager> get_texture_manager() const = 0;
            [[nodiscard]] virtual std::shared_ptr<IMeshManager> get_mesh_manager() const = 0;
            [[nodiscard]] virtual std::shared_ptr<IMaterialManager> get_material_manager() const = 0;

            // Textures
            virtual TextureHandle load_texture(const std::string& file_path) = 0;
            virtual TextureHandle create_texture(const Vec2i& size) = 0;
            virtual TextureHandle create_depth_texture(const Vec2i& size) = 0;
            virtual void delete_texture(const TextureHandle& handle) = 0;

            // Meshes
            virtual MeshHandle load_mesh(const std::string& file_path) = 0;
            virtual MeshHandle generate_mesh(const std::shared_ptr<IMeshGenerator>& mesh_generator) = 0;
            template<class T, class... Args> MeshHandle gen_mesh(Args&&... args) {
                auto generator = std::make_shared<T>(std::forward<Args>(args)...);
                return generate_mesh(generator);
            }
            virtual MeshHandle create_mesh(const std::vector<Vertex>& vertices, const std::vector<u32>& indicies) = 0;

            // Materials
            virtual MaterialHandle create_material(void* properties, const size_t& size) = 0;
            virtual MaterialHandle get_default_material() = 0;

            // Render graph
            std::shared_ptr<IRenderGraph> create_render_graph(const std::string& name);

            // Rendering
            virtual void render(const MeshHandle& mesh_handle, const MaterialHandle& material_handle, const Vec3f& position) = 0;
            virtual void render(const MeshHandle& mesh_handle, const MaterialHandle& material_handle, const Transform& transform) = 0;
            virtual void present() = 0;
    };
}

#endif
