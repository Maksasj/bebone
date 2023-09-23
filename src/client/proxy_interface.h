#ifndef _PROXY_INTERFACE_H_
#define _PROXY_INTERFACE_H_

#include "gpu_handles.h"
#include "transform.h"

using namespace bebone::core;
using namespace bebone::gfx;

class IProxy {
    public:
        virtual ~IProxy() {}

        virtual void preinit() = 0;
        virtual void init() = 0;
        virtual void load() = 0;
        virtual void run() = 0;
        virtual void unload() = 0;
        virtual void cleanup() = 0;
};

#endif
