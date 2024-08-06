#ifndef _BEBONE_RENDERER_IPRESENT_PASS_H_
#define _BEBONE_RENDERER_IPRESENT_PASS_H_

#include "igraphics_pass.h"
#include "mesh/quad_mesh_generator.h"

namespace bebone::renderer {
    class IPresentPass : public IGraphicsPass {
        protected:
            std::shared_ptr<IRenderTarget> target;
            MeshHandle quad_mesh;

        protected:
            std::shared_ptr<IAttachment> texture_attachment;

        public:
            IPresentPass(
                const std::shared_ptr<IPassImpl>& impl,
                const std::string& pass_name,
                const Vec2i& viewport);

            void assemble(IPassAssembler* assember) override;
            void record(ICommandEncoder* encoder) override;
            void reset() override;

            void resize_viewport(const Vec2i& new_size) override;
    };
}

#endif
