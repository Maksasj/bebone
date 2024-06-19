#ifndef _BEBONE_CORE_EVENTS_LISTENERS_EVENT_H_
#define _BEBONE_CORE_EVENTS_LISTENERS_EVENT_H_

namespace bebone::core {
    /*!
     * Base class for all events
     * @tparam EventCategoryType - enumeration that specifies set of possible events
     * @tparam eventType - specific event type
    */
    template<class EventCategoryType, EventCategoryType eventType>
    class Event {
        private:
            bool handled = false;

        public:
            virtual ~Event() = default;

            /*!
             * Function used to setting is event handled or not
             * @param value - value to be set
            */
            void set_handled(const bool& value) {
                handled = value;
            }

            /*!
             * Check if event is handled or not
             * @return - true if event handled, false if not
            */
            const bool& is_handled() const {
                return handled;
            }

            using category = EventCategoryType;
            static constexpr const EventCategoryType type = eventType;
    };
}

#endif