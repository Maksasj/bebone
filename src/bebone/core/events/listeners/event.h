#ifndef _EVENT_H_
#define _EVENT_H_

namespace bebone::core {
    template<class EventType, EventType EventValue>
    struct Event {
        static constexpr const EventType type = EventValue;
    };
}

#endif