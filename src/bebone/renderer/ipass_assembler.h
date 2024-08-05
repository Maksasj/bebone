#ifndef _BEBONE_RENDERER_IPASS_ASSEMBLER_H_
#define _BEBONE_RENDERER_IPASS_ASSEMBLER_H_

#include "iprogram_manager.h"
#include "itexture_manager.h"
#include "imesh_manager.h"
#include "imaterial_manager.h"

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

            virtual std::shared_ptr<IRenderTarget> create_render_target(const std::vector<std::shared_ptr<IAttachment>>& attachments, const Vec2i& viewport) = 0;

            std::shared_ptr<IProgramManager> get_program_manager() const;
            std::shared_ptr<ITextureManager> get_texture_manager() const;
            std::shared_ptr<IMeshManager> get_mesh_manager() const;
            std::shared_ptr<IMaterialManager> get_material_manager() const;
    };
}

#endif
