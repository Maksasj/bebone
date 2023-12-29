#ifndef _EVENT_LISTENER_H_
#define _EVENT_LISTENER_H_

#include <memory>

#include "event.h"

namespace bebone::core {
    using namespace std;

    class EventListener {
    public:
        virtual void handle_event(shared_ptr<Event> event) = 0;
    };
}

#endif