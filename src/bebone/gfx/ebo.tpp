#ifndef _BEBONE_GFX_EBO_TPP_
#define _BEBONE_GFX_EBO_TPP_

#include <vector>

#include "bo.h"

namespace bebone::gfx {
    template<class IndicesType>
    class EBO : public BO {
        public:
            EBO(const std::vector<IndicesType>& indices) {
                glGenBuffers(1, &_ID);

                glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ID);
                glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(IndicesType), indices.data(), GL_STATIC_DRAW);
            }

            void bind() const override {
                glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ID);
            }
            void unbind() const override {
                glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
            };
            
            void terminate() const override {
                glDeleteBuffers(1, &_ID);
            };
    };
}

#endif
