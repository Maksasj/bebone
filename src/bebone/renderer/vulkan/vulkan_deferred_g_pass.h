#ifndef _BEBONE_RENDERER_VULKAN_DEFERRED_G_PASS_H_
#define _BEBONE_RENDERER_VULKAN_DEFERRED_G_PASS_H_

#include "irenderer.h"
#include "ipass.h"
#include "vulkan_command_encoder.h"
#include "vulkan_pass_assembler.h"
#include "vulkan_hdr_texture_resource.h"
#include "vulkan_depth_resource.h"
#include "ideferred_g_pass.h"
#include "vulkan_program.h"

namespace bebone::renderer {
    using namespace bebone::core;
    using namespace bebone::gfx;

    struct VulkanDeferredGPassCameraData {
        Mat4f matrix;
    };

    struct alignas(16) VulkanDeferredGPassHandles {
        Mat4f transform;
        VulkanBindlessBufferHandle camera_handle;
        VulkanBindlessBufferHandle material_handle;
    };

    class VulkanDeferredGPass : public IDeferredGPass {
        private:
            std::shared_ptr<VulkanPipelineLayout> pipeline_layout;

            std::shared_ptr<VulkanRenderPass> render_pass;
            std::vector<std::shared_ptr<VulkanFramebuffer>> framebuffers;

            std::vector<std::shared_ptr<VulkanBufferMemoryTuple>> camera_ubo;
            std::vector<VulkanBindlessBufferHandle> camera_ubo_handles;

            // Reference to mesh manager
            std::shared_ptr<VulkanMeshManager> mesh_manager;

            // Jobs
            static const u32 max_queued_jobs = 1000;
            std::vector<RenderQueueTask> queued_jobs;
            std::vector<Mat4f> queued_jobs_transform;
            std::array<VulkanDeferredGPassHandles, 1000> queued_jobs_handles;

        public:
            VulkanDeferredGPass(const std::string& pass_name, const Vec2i& viewport);

            void assemble(IPassAssembler* assember) override;
            void record(ICommandEncoder* encoder) override;
            void reset() override;

            void resize_viewport(const Vec2i& new_size) override;

            void submit_task(const RenderQueueTask& task, const Transform& transform) override;
    };
}

#endif
