#include <vector>

#include "bexel.h"

using namespace bexel;

int main() {
    PROFILE_RECORD(BEXEL_MAIN)

    Bexel bexel;

    bexel.init();
    bexel.load();
    bexel.run();
    bexel.unload();

    PROFILE_STOP(BEXEL_MAIN)

    bebone::core::Profiler::SumUp();

    return 0;
}
