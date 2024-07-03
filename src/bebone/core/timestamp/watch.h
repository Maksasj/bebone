#ifndef _WATCH_H
#define _WATCH_H

#include "timestamp.h"

namespace bebone::core {
    class Watch {
    private:
        Timestamp current_timestamp;

    public:
        Watch() = default;

        void update_timestamp();
        double get_time_difference();
    };
}

#endif
