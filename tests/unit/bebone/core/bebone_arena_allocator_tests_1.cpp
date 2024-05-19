#include "bebone/core/core.h"
#include "test_shared.h"

int main() {
    using namespace bebone::core;

    TEST_CASE {
        ArenaAllocator arena(_BEBONE_MEMORY_BYTES_1KB_);

        ensure(arena.allocated() == 0);
    }

    TEST_CASE {
        ArenaAllocator arena(_BEBONE_MEMORY_BYTES_1KB_);

        ensure(arena.capacity() == _BEBONE_MEMORY_BYTES_1KB_);
    }

    TEST_CASE {
        ArenaAllocator arena(_BEBONE_MEMORY_BYTES_1KB_);

        int* mem = static_cast<int*>(arena.alloc(sizeof(int)));
        *mem = 69;

        ensure(*mem == 69);
    }

    TEST_CASE {
        ArenaAllocator arena(_BEBONE_MEMORY_BYTES_1KB_);

        int* memInt = static_cast<int*>(arena.alloc(sizeof(int)));
        *memInt = 69;

        struct Data{ int data[16]; };

        Data* memData = static_cast<Data*>(arena.alloc(sizeof(Data)));
        *memData = Data();

        ensure(*memInt == 69);
    }

    TEST_CASE {
        ArenaAllocator arena(_BEBONE_MEMORY_BYTES_1KB_);

        {
            int* memInt = static_cast<int*>(arena.alloc(sizeof(int)));
            *memInt = 420;
        }

        arena.clear();

        int* memInt = static_cast<int*>(arena.alloc(sizeof(int)));
        *memInt = 69;

        ensure(*memInt == 69);
    }

    TEST_CASE {
        ArenaAllocator arena(sizeof(char));

        char* memChar = static_cast<char*>(arena.alloc(sizeof(char)));
        *memChar = 25;
        ensure(*memChar == 25);

        void* ptr = arena.alloc(sizeof(size_t));
        ensure(ptr == nullptr);
    }

    return 0;
}