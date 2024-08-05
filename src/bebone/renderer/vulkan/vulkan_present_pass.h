#ifndef _BEBONE_RENDERER_VULKAN_PRESENT_PASS_H_
#define _BEBONE_RENDERER_VULKAN_PRESENT_PASS_H_

#include "mesh/quad_mesh_generator.h"
#include "vulkan_triangle_mesh_builder.h"
#include "irenderer.h"
#include "ipass.h"
#include "vulkan_command_encoder.h"
#include "vulkan_pass_assembler.h"
#include "vulkan_hdr_texture_attachment.h"
#include "vulkan_depth_attachment.h"
#include "vulkan_program.h"

namespace bebone::renderer {
    using namespace bebone::gfx;

    class VulkanPresentPass : public IPresentPass {
        private:
            std::shared_ptr<VulkanMeshManager> mesh_manager;
            MeshHandle quad_mesh;

        public:
            VulkanPresentPass(const std::string& pass_name, const Vec2i& viewport);

            void assemble(IPassAssembler* assember) override;
            void record(ICommandEncoder* encoder) override;
            void reset() override;

            void resize_viewport(const Vec2i& new_size) override;
    };
}

#endif
