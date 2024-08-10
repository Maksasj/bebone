#ifndef _BEBONE_RENDERER_IPASS_ASSEMBLER_H_
#define _BEBONE_RENDERER_IPASS_ASSEMBLER_H_

#include "iprogram_manager.h"
#include "itexture_manager.h"
#include "imesh_manager.h"
#include "imaterial_manager.h"
#include "ipass_impl.h"
#include "irender_target.h"
#include "iattachment.h"
#include "iuniform_buffer.h"

namespace bebone::renderer {
    class IPassAssembler {
        private:
            std::shared_ptr<IProgramManager> program_manager;
            std::shared_ptr<ITextureManager> texture_manager;
            std::shared_ptr<IMeshManager> mesh_manager;
            std::shared_ptr<IMaterialManager> material_manager;

        public:
            IPassAssembler(
                const std::shared_ptr<IProgramManager>& program_manager,
                const std::shared_ptr<ITextureManager>& texture_manager,
                const std::shared_ptr<IMeshManager>& mesh_manager,
                const std::shared_ptr<IMaterialManager>& material_manager);

            virtual std::shared_ptr<IUniformBuffer> create_uniform_buffer(const size_t& size) = 0;
            std::shared_ptr<IProgram> create_program(const std::shared_ptr<IPassImpl>& impl, const std::string& vertex_shader_code, const std::string& fragment_shader_code);

            // Todo move this out
            virtual std::shared_ptr<IRenderTargetImpl> create_present_target_impl() = 0;
            virtual std::shared_ptr<IRenderTargetImpl> create_render_target_impl(
                const std::shared_ptr<IPassImpl>& pass_impl,
                const std::vector<std::shared_ptr<IAttachment>>& attachments,
                const Vec2i& viewport) = 0;

            std::shared_ptr<IProgramManager> get_program_manager() const;
            std::shared_ptr<ITextureManager> get_texture_manager() const;
            std::shared_ptr<IMaterialManager> get_material_manager() const;

            std::shared_ptr<IMeshManager> get_mesh_manager() const;
            MeshHandle get_default_quad() const;
            MeshHandle get_default_cube() const;
    };
}

#endif
