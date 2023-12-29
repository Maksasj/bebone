#ifndef _EVENT_OBSERVER_H_
#define _EVENT_OBSERVER_H_

#include <vector>
#include <memory>
#include <map>

#include "event_listener.h"
#include "event.h"

namespace bebone::core {
    template <typename T>
    class EventObserver {
    private:
        vector<shared_ptr<EventListener<T>>> listeners;
    public:
        EventObserver() : listeners(vector<shared_ptr<EventListener<T>>>()) {
            static_assert(std::is_base_of<Event, T>::value, "T must be a bebone::core::Event derivative");
        }

        void add_listener(shared_ptr<EventListener<T>> eventListener) {
            listeners.push_back(eventListener);
        }

        void remove_listener(shared_ptr<EventListener<T>> eventListener) {
            auto it = find(listeners.begin(), listeners.end(), eventListener);

            if (it != listeners.end()) {
                listeners.erase(it);
            }
        }

        void fire_event(shared_ptr<T> event) {
            for (const auto& listener : listeners) {
                listener->handle_event(event);
            }
        }
    };
}

#endif