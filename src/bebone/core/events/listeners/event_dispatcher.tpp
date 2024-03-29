#ifndef _BEBONE_CORE_EVENTS_LISTENERS_EVENT_DISPATCHER_H_
#define _BEBONE_CORE_EVENTS_LISTENERS_EVENT_DISPATCHER_H_

#include <map>
#include <functional>

#include "event_listener.tpp"
#include "event.tpp"

#include "../../meta/function_traits.tpp"

namespace bebone::core {
    /*!
     * Class that is used for dispatching events, you can add listener to dispatcher and then fire needed events
     * @tparam EventCategory - enumeration that specifies set of possible events
    */
    template<typename EventCategory>
    class EventDispatcher {
        private:
            std::multimap<EventCategory, std::shared_ptr<void>> callbacks;

        public:
            /// Meta function that checks if event is suitable for this event dispatcher
            template<typename EventType>
            using is_suitable_event_type = std::enable_if_t<std::is_same<typename EventType::category, EventCategory>::value>;

            /*!
             * Function that sends event to desired event listeners
             * @tparam EventType - type of the event
             * @param event - event object
            */
            template<typename EventType, typename = is_suitable_event_type<EventType>>
            void fire(EventType event) {
                const EventCategory eventType = EventType::type;
                auto rng = callbacks.equal_range(eventType);

                for (auto it = rng.first; it != rng.second; ++it) {
                    void* ptr = it->second.get();

                    using CallbackType = std::function<void(EventType&)>;

                    auto f = *static_cast<CallbackType*>(ptr);

                    f(event);

                    if(event.is_handled())
                        break;
                }
            }

            /// Helper meta function, that extracts type of the first argument of callable type
            template<typename Listener>
            using first_arg = typename function_traits<Listener>::template argument<0>;

            /// Meta function that checks if listener is suitable for this event dispatcher
            template<typename Listener>
            using is_suitable_listener = std::enable_if_t<std::is_same<typename std::remove_reference<first_arg<Listener>>::type::category, EventCategory>::value>;

            /*!
             * Function that add listener to dispatcher
             * @tparam Listener - type of the event listener
             * @param listener - listener object
            */
            template<typename Listener, typename = is_suitable_listener<Listener>>
            void add_listener(Listener listener) {
                using EventType = typename function_traits<Listener>::template argument<0>;

                auto ptr = std::make_shared<std::function<void(EventType)>>(listener);

                const EventCategory eventType = std::remove_reference<EventType>::type::type;
                callbacks.emplace(eventType, ptr);
            }

            /*!
             * Function that clears all listeners
            */
            void flush_listeners() noexcept {
                callbacks.clear();
            }
    };
}

#endif