#include "bo.h"

using namespace bebone::gfx;

unsigned long BO::get_id() const {
    return _ID; 
}

unsigned long* BO::get_id_ref() {
    return &_ID;
}
