#ifndef _EVENT_OBSERVER_H_
#define _EVENT_OBSERVER_H_

#include <map>
#include <functional>

#include "event_listener.tpp"
#include "event.tpp"

#include "../../meta/function_traits.tpp"

namespace bebone::core {
    template<class EventCategory>
    class EventDispatcher {
        private:
            std::multimap<EventCategory, std::shared_ptr<void>> callbacks;

        public:
            template<typename EventType>
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

            template<typename Listener>
            void add_listener(Listener listener) {
                using EventType = function_traits<Listener>::template argument<0>;

                auto ptr = std::make_shared<std::function<void(EventType)>>(listener);

                const EventCategory eventType = std::remove_reference<EventType>::type::type;
                callbacks.emplace(eventType, ptr);
            }

            void flush_listeners() noexcept {
                callbacks.clear();
            }
    };
}

#endif