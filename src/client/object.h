#ifndef _OBJECT_H_
#define _OBJECT_H_

#include "renderer.h"

using namespace bebone::core;

struct Object {
    Vec3f position;
    f32 scale; // Todo make this a vector
    Vec3f rotation;

    Vec3f velocity;
    Vec3f force;
    f32 mass;

    Renderer* renderer = nullptr;

    public:
        ~Object() {
            if(renderer != nullptr)
                delete renderer;
        }
};

#endif
