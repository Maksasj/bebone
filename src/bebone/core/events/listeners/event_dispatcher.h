#ifndef _EVENT_OBSERVER_H_
#define _EVENT_OBSERVER_H_

#include <vector>
#include <memory>
#include <map>

#include "event_listener.h"
#include "event.h"


template<typename F>
struct CallableTraits : public CallableTraits<decltype(&F::operator())> {};

template<typename R, typename C, typename... Args>
struct CallableTraits<R(C::*)(Args...) const> {
    using Arg1Type = std::tuple_element_t<0, std::tuple<Args...>>;
};

template<typename F>
using Arg1Type = typename CallableTraits<F>::Arg1Type;

// Tricky thing, but it works
template < template <typename...> class base,typename derived>
struct is_base_of_template_impl {
    template<typename... Ts>
    static constexpr std::true_type  test(const base<Ts...> *);
    static constexpr std::false_type test(...);
    using type = decltype(test(std::declval<derived*>()));
};

template < template <typename...> class base,typename derived>
using is_base_of_template = typename is_base_of_template_impl<base,derived>::type;

template<typename Function>
struct function_traits;

// specialization for member functions
template<typename Class, typename Result, typename... Args>
struct function_traits<Result(Class::*)(Args...)> {
    using first_argument_type = std::tuple_element_t<0, std::tuple<Args...>>;
};

namespace bebone::core {
    template<class EventType>
    class EventDispatcher {
        private:
            std::multimap<EventType, std::shared_ptr<void>> callbacks;

        public:
            template<typename Event>
            void fire(Event event) {
                const EventType eventType = Event::type;
                auto rng = callbacks.equal_range(eventType);

                for (auto it = rng.first; it != rng.second; ++it) {
                    void* ptr = it->second.get();

                    using CallableType = std::function<void(Event)>;

                    auto f = *static_cast<CallableType*>(ptr);

                    f(event);
                }
            }

            // template<typename F>
            // using LambdaType = void (*)(F);

            template<typename Event>
            void add_listener(void (*function)(Event)) {
                auto ptr = std::make_shared<std::function<void(Event)>>(function);

                const EventType eventType = Event::type;
                callbacks.emplace(eventType, ptr);
            }

            template<typename Callable, std::enable_if_t<is_base_of_template<EventListener, Callable>::value>* = nullptr>
            void add_listener(Callable listener) {
                using OperatorMethod = decltype(&Callable::operator());
                using Event = function_traits<OperatorMethod>::first_argument_type;

                auto ptr = std::make_shared<std::function<void(Event)>>(listener);

                const EventType eventType = Event::type;
                callbacks.emplace(eventType, ptr);
            }

            template<typename Callable, std::enable_if_t<!is_base_of_template<EventListener, Callable>::value>* = nullptr>
            void add_listener(Callable lambda) {
                using Event = Arg1Type<Callable>;

                auto ptr = std::make_shared<std::function<void(Event)>>(lambda);

                const EventType eventType = Event::type;
                callbacks.emplace(eventType, ptr);
            }
    };
}

#endif