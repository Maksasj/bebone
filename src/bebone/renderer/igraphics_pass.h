#ifndef _BEBONE_RENDERER_IGRAPHICS_PASS_H_
#define _BEBONE_RENDERER_IGRAPHICS_PASS_H_

#include "ipass.h"
#include "iprogram.h"

namespace bebone::renderer {
    using namespace bebone::core;

    class IGraphicsPass : public IPass {
        protected:
            std::shared_ptr<IProgram> program;
            bool program_set_flag;

            Vec2i viewport;

        public:
            IGraphicsPass(const std::string& pass_name, const Vec2i& viewport);

            void check_requirements() override;

            void set_program(const std::shared_ptr<IProgram>& arg_program);
            std::shared_ptr<IProgram> get_program() const;

            const Vec2i& get_viewport() const;
    };
}

#endif
