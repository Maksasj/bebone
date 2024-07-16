#ifndef _BEBONE_RENDERER_VULKAN_PASS_ASSEMBLER_H_
#define _BEBONE_RENDERER_VULKAN_PASS_ASSEMBLER_H_

#include "../renderer_backend.h"
#include "ipass_assembler.h"
#include "vulkan_program_manager.h"

namespace bebone::renderer {
    using namespace bebone::gfx;

    class VulkanPassAssembler : public IPassAssembler {
        private:
            std::shared_ptr<VulkanDevice> device;
            std::shared_ptr<VulkanSwapChain> swap_chain;
            std::shared_ptr<VulkanProgramManager> program_manager;

        public:
            VulkanPassAssembler(
                const std::shared_ptr<VulkanDevice>& device,
                const std::shared_ptr<VulkanSwapChain>& swap_chain,
                const std::shared_ptr<VulkanProgramManager>& program_manager);

            std::shared_ptr<VulkanDevice> get_device() const;
            std::shared_ptr<VulkanSwapChain> get_swap_chain() const;
            std::shared_ptr<VulkanProgramManager> get_program_manager() const;
    };
}

#endif