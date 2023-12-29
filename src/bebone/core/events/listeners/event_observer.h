#ifndef _EVENT_OBSERVER_H_
#define _EVENT_OBSERVER_H_

#include <vector>
#include <memory>
#include <map>

#include "event_listener.h"
#include "event.h"

namespace bebone::core {
    class EventObserver {
    private:
        vector<shared_ptr<EventListener>> listeners;
    public:
        EventObserver();

        void add_listener(shared_ptr<EventListener> eventListener);
        void remove_listener(shared_ptr<EventListener> eventListener);

        void fire_event(shared_ptr<Event> event);
    };
}

#endif