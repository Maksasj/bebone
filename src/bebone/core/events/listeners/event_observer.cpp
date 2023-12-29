#include "event_observer.h"

namespace bebone::core {
    EventObserver::EventObserver() : listeners(vector<shared_ptr<EventListener>>()) { }

    void EventObserver::add_listener(shared_ptr<bebone::core::EventListener> eventListener) {
        listeners.push_back(eventListener);
    }

    void EventObserver::remove_listener(shared_ptr<bebone::core::EventListener> eventListener) {
        auto it = find(listeners.begin(), listeners.end(), eventListener);

        if (it != listeners.end()) {
            listeners.erase(it);
        }
    }

    void EventObserver::fire_event(shared_ptr<bebone::core::Event> event) {
        for (const auto& listener : listeners) {
            listener->handle_event(event);
        }
    }
}