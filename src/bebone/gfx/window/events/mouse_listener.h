#ifndef _MOUSE_LISTENER_H_
#define _MOUSE_LISTENER_H_

#include "../../../core/core.h"
#include "input_event.h"

namespace bebone::gfx {
    using namespace core;

    class MouseListener : EventListener<InputMouseButtonEvent> {
    private:
        std::shared_ptr<InputExecutor>& input_executor;

    public:
        MouseListener() = delete;
        explicit MouseListener(std::shared_ptr<InputExecutor>& input_executor);

        void operator()(InputMouseButtonEvent& event) override;
    };
}

#endif
