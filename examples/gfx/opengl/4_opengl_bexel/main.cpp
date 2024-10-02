#include <vector>

#include "bexel.h"

using namespace bexel;

int main() {
    Bexel bexel;

    bexel.init();
    bexel.load();
    bexel.run();
    bexel.unload();

    return 0;
}
