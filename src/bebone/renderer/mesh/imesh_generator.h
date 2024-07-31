#ifndef _BEBONE_RENDERER_IMESH_GENERATOR_H_
#define _BEBONE_RENDERER_IMESH_GENERATOR_H_

#include <fstream>

#include "renderer_backend.h"
#include "imesh_builder.h"

namespace bebone::renderer {
    template<class Vertex>
    class IMeshGenerator {
        protected:

        public:
            virtual ~IMeshGenerator() = default;

            virtual std::shared_ptr<IMesh> generate(const std::shared_ptr<IMeshBuilder<Vertex>>& builder) = 0;
    };

}

#endif
