#ifndef _CAMERA_TRANSFORM_H_
#define _CAMERA_TRANSFORM_H_

#include "client_backend.h"

using namespace bebone::core;

struct CameraTransform {
    Mat4f view;
    Mat4f proj;
};

#endif
