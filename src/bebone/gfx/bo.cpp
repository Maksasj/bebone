#include "bo.h"

using namespace bebone::gfx;

unsigned int BO::get_id() const {
    return _ID; 
}

unsigned int* BO::get_id_ref() {
    return &_ID;
}
