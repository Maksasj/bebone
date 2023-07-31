#ifndef _BEBONE_GFX_OPENGL_BUFFER_OBJECT_H_
#define _BEBONE_GFX_OPENGL_BUFFER_OBJECT_H_

#include "../i_buffer_object.h"

#include "../gfx_backend.h"

namespace bebone::gfx {
    class GLBufferObject : public IBufferObject {
        protected:
            unsigned int _ID;

        public:
            void bind() const override {};
            void unbind() const override {};
            
            void terminate() const override {};

            unsigned int get_id() const;
            unsigned int* get_id_ref();
    };
}
#endif
