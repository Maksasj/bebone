#ifndef _BEBONE_RENDERER_IRENDERER_H_
#define _BEBONE_RENDERER_IRENDERER_H_

#include "renderer_backend.h"

#include "irender_graph.h"
#include "ipass.h"

#include "itexture.h"

#include "imaterial.h"
#include "imaterial_impl.h"

#include "mesh/imesh.h"
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
    struct ModelHandle { size_t index; };

    class IRenderer : public NonCopyable {
        private:
            const GfxAPI api;

        protected:
            virtual void resize_viewport(const Vec2i& new_size) = 0;

            std::shared_ptr<IRenderGraph> create_default_render_graph(const Vec2i& viewport);

        public:
            IRenderer(const GfxAPI& api);
            virtual ~IRenderer() = default;

            virtual std::shared_ptr<IProgramManager> get_program_manager() const = 0;
            virtual std::shared_ptr<ITextureManager> get_texture_manager() const = 0;
            virtual std::shared_ptr<IMeshManager> get_mesh_manager() const = 0;
            virtual std::shared_ptr<IMaterialManager> get_material_manager() const = 0;

            virtual TextureHandle load_texture(const std::string& file_path) = 0;

            virtual MeshHandle load_mesh(const std::string& file_path) = 0;
            virtual MeshHandle generate_mesh(const std::shared_ptr<IMeshGenerator<Vertex>>& mesh_generator) = 0;
            virtual MeshHandle create_mesh(const std::vector<Vertex>& vertices, const std::vector<u32>& indicies) = 0;

            virtual MaterialHandle create_material(void* properties, const size_t& size) = 0;
            virtual MaterialHandle default_material() = 0;

            virtual void render(const MeshHandle& mesh_handle, const MaterialHandle& material_handle, const Transform& transform) = 0;
            virtual void present() = 0;

            virtual std::shared_ptr<IRenderGraphImpl> create_render_graph_impl() = 0;
            std::shared_ptr<IRenderGraph> create_render_graph(const std::string& name);

            const GfxAPI& get_api() const;
    };
}

#endif
