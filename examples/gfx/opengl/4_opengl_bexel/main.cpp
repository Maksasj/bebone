#include <vector>

#include "bexel.h"

using namespace bexel;

int main() {
    BEBONE_PROFILE_RECORD(BEXEL_MAIN)

    Bexel bexel;

    bexel.init();
    bexel.load();
    bexel.run();
    bexel.unload();

    BEBONE_PROFILE_STOP(BEXEL_MAIN)

    bebone::core::Profiler::get_instance().sum_up();

    return 0;
}
