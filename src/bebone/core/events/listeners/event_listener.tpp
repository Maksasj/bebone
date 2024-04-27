#ifndef _BEBONE_CORE_EVENTS_LISTENERS_EVENT_LISTENER_H_
#define _BEBONE_CORE_EVENTS_LISTENERS_EVENT_LISTENER_H_

#include "event.tpp"

namespace bebone::core {
    using namespace std;

    /*!
     * Base class for all event listeners
     * @tparam EventType event to listen
    */
    template<class EventType>
    class EventListener {
        private:

        public:
            virtual ~EventListener() = default;
            
            virtual void operator()(EventType&) = 0;
    };
}

#endif