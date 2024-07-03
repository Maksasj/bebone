#include "watch.h"

namespace bebone::core {
    void Watch::update_timestamp() {
        current_timestamp = Timestamp();
    }

    double Watch::get_time_difference() {
        Timestamp now;
        return now - current_timestamp;
    }
}