#ifndef _TRANSFORM_H_
#define _TRANSFORM_H_

#include "client_backend.h"

using namespace bebone::core;

struct Transform {
    Mat4f transform;
    Mat4f scale;
    Mat4f rotation;
};

#endif
