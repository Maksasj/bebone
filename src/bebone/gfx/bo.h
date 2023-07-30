#ifndef _BEBONE_GFX_BO_H_
#define _BEBONE_GFX_BO_H_

#include "gfx_backend.h"

namespace bebone::gfx {
    class BO {
        protected:
            unsigned int _ID;

        public:
            virtual void bind() const {};
            virtual void unbind() const {};
            
            virtual void terminate() const {};

            unsigned int get_id() const;
            unsigned int* get_id_ref();
    };
}
#endif
