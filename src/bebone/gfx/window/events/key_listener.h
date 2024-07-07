#ifndef _KEY_LISTENER_H_
#define _KEY_LISTENER_H_

#include "../../../core/core.h"
#include "input_event.h"

namespace bebone::gfx {
    using namespace core;

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
