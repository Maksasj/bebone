#include "ipass_assembler.h"

namespace bebone::renderer {
    IPassAssembler::IPassAssembler(
        const std::shared_ptr<IProgramManager>& program_manager,
        const std::shared_ptr<ITextureManager>& texture_manager,
        const std::shared_ptr<IMeshManager>& mesh_manager,
        const std::shared_ptr<IMaterialManager>& material_manager
    ) : program_manager(program_manager), texture_manager(texture_manager), mesh_manager(mesh_manager), material_manager(material_manager) {
    }

    std::shared_ptr<IProgram> IPassAssembler::create_program(
        const std::shared_ptr<IPassImpl>& impl,
        const std::string& vertex_shader_code,
        const std::string& fragment_shader_code
    ) {
        return program_manager->create_program(impl, vertex_shader_code, fragment_shader_code);
    }

    std::shared_ptr<IProgramManager> IPassAssembler::get_program_manager() const {
        return program_manager;
    }

    CachedProgramSource IPassAssembler::get_shader_source(const std::string& name) const {
        return program_manager->get_source(name);
    }

    std::shared_ptr<ITextureManager> IPassAssembler::get_texture_manager() const {
        return texture_manager;
    }

    std::shared_ptr<IMeshManager> IPassAssembler::get_mesh_manager() const {
        return mesh_manager;
    }

    MeshHandle IPassAssembler::get_default_quad() const {
        return mesh_manager->get_default_quad();
    }

    MeshHandle IPassAssembler::get_default_cube() const {
        return mesh_manager->get_default_cube();
    }

    std::shared_ptr<IMaterialManager> IPassAssembler::get_material_manager() const {
        return material_manager;
    }
}

