#ifndef _EVENT_LISTENER_H_
#define _EVENT_LISTENER_H_

#include <memory>

#include "event.h"

namespace bebone::core {
    using namespace std;

    template<class EventType>
    struct EventListener {
        virtual void operator()(EventType) = 0;
    };
}

#endif