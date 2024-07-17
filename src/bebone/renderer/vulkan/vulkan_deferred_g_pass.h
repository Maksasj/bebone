#ifndef _BEBONE_RENDERER_VULKAN_DEFERRED_G_PASS_H_
#define _BEBONE_RENDERER_VULKAN_DEFERRED_G_PASS_H_

#include "../irenderer.h"
#include "../ipass.h"
#include "vulkan_command_encoder.h"
#include "vulkan_pass_assembler.h"
#include "vulkan_hdr_texture_resource.h"
#include "vulkan_depth_resource.h"
#include "../ideferred_g_pass.h"
#include "vulkan_program.h"

namespace bebone::renderer {
    using namespace bebone::core;
    using namespace bebone::gfx;

    struct VulkanDeferredGPassModelData {
        Mat4f transform;
    };

    struct VulkanDeferredGPassCameraData {
        Mat4f matrix;
    };

    struct VulkanDeferredGPassHandles {
        VulkanBindlessBufferHandle model_handle;
        u32 model_instance;
        VulkanBindlessBufferHandle camera_handle;
    };

    class VulkanDeferredGPass : public IDeferredGPass {
        private:
            std::shared_ptr<VulkanRenderPass> render_pass;
            std::vector<std::shared_ptr<VulkanFramebuffer>> framebuffers;

            std::vector<std::shared_ptr<VulkanBufferMemoryTuple>> model_ubo;
            std::vector<VulkanBindlessBufferHandle> model_ubo_handles;

            std::vector<std::shared_ptr<VulkanBufferMemoryTuple>> camera_ubo;
            std::vector<VulkanBindlessBufferHandle> camera_ubo_handles;

            // Jobs
            static const u32 max_queued_jobs = 50;
            std::vector<std::shared_ptr<IModel>> queued_jobs_model;
            std::vector<Mat4f> queued_jobs_transform;
            std::array<VulkanDeferredGPassHandles, 50> queued_jobs_handles;

        public:
            VulkanDeferredGPass(const std::string& pass_name, const Vec2i& viewport);

            void assemble(IPassAssembler* assember) override;
            void record(ICommandEncoder* encoder) override;
            void reset() override;

            void resize_viewport(const Vec2i& new_size) override;

            void submit_task(const std::shared_ptr<IModel>& model, const Transform& transform) override;
    };
}

#endif
