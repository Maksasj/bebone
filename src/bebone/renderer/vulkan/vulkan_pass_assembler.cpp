#include "vulkan_pass_assembler.h"

namespace bebone::renderer {
    VulkanPassAssembler::VulkanPassAssembler(
        const std::shared_ptr<VulkanDevice>& device,
        const std::shared_ptr<VulkanSwapChain>& swap_chain,
        const std::shared_ptr<VulkanProgramManager>& program_manager,
        const std::shared_ptr<VulkanTextureManager>& texture_manager,
        const std::shared_ptr<VulkanMeshManager>& mesh_manager
    ) : device(device), swap_chain(swap_chain), program_manager(program_manager), texture_manager(texture_manager), mesh_manager(mesh_manager) {


    }

    std::shared_ptr<VulkanDevice> VulkanPassAssembler::get_device() const {
        return device;
    }

    std::shared_ptr<VulkanSwapChain> VulkanPassAssembler::get_swap_chain() const {
        return swap_chain;
    }

    std::shared_ptr<VulkanProgramManager> VulkanPassAssembler::get_program_manager() const {
        return program_manager;
    }

    std::shared_ptr<VulkanTextureManager> VulkanPassAssembler::get_texture_manager() const {
        return texture_manager;
    }

    std::shared_ptr<VulkanMeshManager> VulkanPassAssembler::get_mesh_manager() const {
        return mesh_manager;
    }
}
