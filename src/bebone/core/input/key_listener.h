#ifndef _KEY_LISTENER_H_
#define _KEY_LISTENER_H_

#include "../events/listeners/event_listener.tpp"

#include "../../gfx/window/events/input_event.h"

#include "input_executor.h"

namespace bebone::core {
    using namespace gfx;

    class KeyListener : EventListener<InputKeyEvent> {
    private:
        std::shared_ptr<InputExecutor>& input_executor;

    public:
        KeyListener() = delete;
        explicit KeyListener(std::shared_ptr<InputExecutor>& input_executor);

        void operator()(InputKeyEvent& event) override;
    };
}

#endif
