#ifndef _BEBONE_RENDERER_VULKAN_PRESENT_PASS_H_
#define _BEBONE_RENDERER_VULKAN_PRESENT_PASS_H_

#include "../mesh/quad_mesh_generator.h"
#include "vulkan_triangle_mesh_builder.h"
#include "../irenderer.h"
#include "../ipass.h"
#include "vulkan_command_encoder.h"
#include "vulkan_pass_assembler.h"
#include "vulkan_texture_resource.h"
#include "vulkan_depth_resource.h"

namespace bebone::renderer {
    using namespace bebone::gfx;

    class VulkanPresentPass : public IPresentPass {
        private:
            std::optional<VulkanManagedPipelineTuple> pipeline;
            std::shared_ptr<IMesh> quad_mesh;
            std::vector<VulkanBindlessHandle> texture_handles;

        public:
            VulkanPresentPass(const std::string& pass_name);

            void assemble(IPassAssembler* assember) override;

            void record(ICommandEncoder* encoder) override;
            void reset() override;
    };
}

#endif