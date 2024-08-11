#ifndef _BEBONE_RENDERER_IMESH_GENERATOR_H_
#define _BEBONE_RENDERER_IMESH_GENERATOR_H_

#include <fstream>

#include "renderer_backend.h"
#include "imesh_builder.h"

namespace bebone::renderer {
    class IMeshGenerator {
        protected:

        public:
            virtual ~IMeshGenerator() = default;

            virtual void append_vertices(const std::shared_ptr<IMeshBuilder>& builder) = 0;
            virtual std::shared_ptr<IMeshImpl> generate(const std::shared_ptr<IMeshBuilder>& builder) = 0;
    };

}

#endif
