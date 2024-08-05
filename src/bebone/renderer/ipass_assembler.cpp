#include "ipass_assembler.h"

namespace bebone::renderer {
    IPassAssembler::IPassAssembler(
        const std::shared_ptr<IProgramManager>& program_manager,
        const std::shared_ptr<ITextureManager>& texture_manager,
        const std::shared_ptr<IMeshManager>& mesh_manager,
        const std::shared_ptr<IMaterialManager>& material_manager
    ) : program_manager(program_manager), texture_manager(texture_manager), mesh_manager(mesh_manager), material_manager(material_manager) {
    }

    std::shared_ptr<IProgramManager> IPassAssembler::get_program_manager() const {
        return program_manager;
    }
    std::shared_ptr<ITextureManager> IPassAssembler::get_texture_manager() const {
        return texture_manager;
    }
    std::shared_ptr<IMeshManager> IPassAssembler::get_mesh_manager() const {
        return mesh_manager;
    }
    std::shared_ptr<IMaterialManager> IPassAssembler::get_material_manager() const {
        return material_manager;
    }
}

