#ifndef _BEBONE_RENDERER_IDEFERRED_G_PASS_H_
#define _BEBONE_RENDERER_IDEFERRED_G_PASS_H_

#include <string>
#include "irender_queue_pass.h"

namespace bebone::renderer {
    using namespace bebone::core;
    using namespace bebone::gfx;

    class IDeferredGPass : public IRenderQueuePass {
        private:
            std::shared_ptr<IRenderTarget> target;
            std::shared_ptr<IUniformBuffer> camera_ubo;

            // Jobs
            std::vector<RenderQueueTask> queued_jobs;

        protected:
            std::shared_ptr<IAttachment> position_attachment;
            std::shared_ptr<IAttachment> normals_attachment;
            std::shared_ptr<IAttachment> albedo_attachment;
            std::shared_ptr<IAttachment> specular_attachment;

            std::shared_ptr<IAttachment> depth_attachment;

        public:
            IDeferredGPass(const std::shared_ptr<IPassImpl>& impl, const std::string& pass_name, const Vec2i& viewport);

            void assemble(IPassAssembler* assember) override;
            void record(ICommandEncoder* encoder) override;
            void reset() override;

            void resize_viewport(const Vec2i& new_size) override;

            void submit_task(const RenderQueueTask& task) override;
    };
}

#endif
