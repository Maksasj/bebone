#ifndef _BEBONE_GFX_BO_H_
#define _BEBONE_GFX_BO_H_

namespace bebone::gfx {
    class BO {
        protected:
            unsigned long _ID;

        public:
            virtual void bind() const {};
            virtual void unbind() const {};
            
            virtual void terminate() const {};

            unsigned long get_id() const;
            unsigned long* get_id_ref();
    };
}
#endif
