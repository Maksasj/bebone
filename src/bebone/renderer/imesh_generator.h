#ifndef _BEBONE_RENDERER_IMESH_GENERATOR_H_
#define _BEBONE_RENDERER_IMESH_GENERATOR_H_

#include <fstream>

#include "renderer_backend.h"
#include "imesh_builder.h"

namespace bebone::renderer {
    class IMeshGenerator {
        protected:
            std::shared_ptr<IMeshBuilder> builder;

        public:
            IMeshGenerator(const std::shared_ptr<IMeshBuilder>& builder);
            virtual ~IMeshGenerator() = default;

            virtual void reset() = 0;
            virtual std::shared_ptr<IMesh> generate() = 0;
    };

}

#endif
