#ifndef _BEBONE_CORE_EVENTS_LISTENERS_EVENT_LISTENER_H_
#define _BEBONE_CORE_EVENTS_LISTENERS_EVENT_LISTENER_H_

#include "event.tpp"

namespace bebone::core {
    using namespace std;

    template<class EventType>
    class EventListener {
        private:

        public:
            virtual void operator()(EventType&) = 0;
    };
}

#endif