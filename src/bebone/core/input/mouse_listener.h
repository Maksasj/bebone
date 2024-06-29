#ifndef _MOUSE_LISTENER_H_
#define _MOUSE_LISTENER_H_

#include "../events/listeners/event_listener.tpp"

#include "../../gfx/window/events/input_event.h"

#include "input.h"

namespace bebone::core {
    using namespace gfx;

    class MouseListener : EventListener<InputMouseButtonEvent> {
    private:
        std::shared_ptr<Input>& input;

    public:
        MouseListener() = delete;
        explicit MouseListener(std::shared_ptr<Input>& input);

        void operator()(InputMouseButtonEvent& event) override;
    };
}

#endif
