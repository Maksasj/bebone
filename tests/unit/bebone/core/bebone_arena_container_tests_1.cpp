#include "bebone/core/core.h"
#include "test_shared.h"

int main() {
    using namespace bebone::core;

    TEST_CASE {
        ArenaContainer container(_BEBONE_MEMORY_BYTES_1KB_);

        int* e1 = static_cast<int*>(container.alloc(sizeof(int)));
        int* e2 = static_cast<int*>(container.alloc(sizeof(int)));
        int* e3 = static_cast<int*>(container.alloc(sizeof(int)));

        *e1 = 16;
        *e2 = 32;
        *e3 = 64;

        int* ee1 = static_cast<int*>(container.at(0));
        int* ee2 = static_cast<int*>(container.at(1));
        int* ee3 = static_cast<int*>(container.at(2));

        ensure(*ee1 == *e1);
        ensure(*ee2 == *e2);
        ensure(*ee3 == *e3);

        ensure(container.size() == 3);
    }

    TEST_CASE {
        ArenaContainer container(_BEBONE_MEMORY_BYTES_1KB_ * 256);

        for(int i = 0; i < 100; ++i) {
            int* e = static_cast<int*>(container.alloc(sizeof(int)));
            *e = i;

            ensure(container.size() == static_cast<size_t>(i + 1));
        }

        for(int i = 0; i < 100; ++i) {
            int* e = static_cast<int*>(container.at(i));
            ensure(*e == i);
        }

        ensure(container.size() == 100);
    }

    TEST_CASE {
        ArenaContainer container(_BEBONE_MEMORY_BYTES_1KB_ * 256);

        for(int i = 0; i < 100; ++i) {
            int* e = static_cast<int*>(container.alloc(sizeof(int)));
            *e = i;

            ensure(container.size() == static_cast<size_t>(i + 1));
        }

        container.clear();

        ensure(container.size() == 0);
    }

    return 0;
}