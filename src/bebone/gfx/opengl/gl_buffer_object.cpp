#include "gl_buffer_object.h"

using namespace bebone::gfx;

unsigned int GLBufferObject::get_id() const {
    return _ID; 
}

unsigned int* GLBufferObject::get_id_ref() {
    return &_ID;
}
