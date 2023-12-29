#ifndef _EVENT_LISTENER_H_
#define _EVENT_LISTENER_H_

#include <memory>

#include "event.h"

namespace bebone::core {
    using namespace std;

    template <typename T>
    class EventListener {
    public:
        EventListener() {
            static_assert(std::is_base_of<Event, T>::value, "T must be a bebone::core::Event derivative");
        }

        virtual void handle_event(shared_ptr<T> event) = 0;
    };
}

#endif