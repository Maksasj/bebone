#include "bebone/core/core.h"
#include "gtest/gtest.h"

using namespace bebone::core;

TEST(ArenaAllocatorTestSuite, AllocationCheckAfterInitialization) {
    ArenaAllocator arena(BEBONE_MEMORY_BYTES_1KB);

    ASSERT_EQ(arena.get_allocated(), 0);
}

TEST(ArenaAllocatorTestSuite, CapacityCheckAfterInitialization) {
    ArenaAllocator arena(BEBONE_MEMORY_BYTES_1KB);

    ASSERT_EQ(arena.get_capacity(), BEBONE_MEMORY_BYTES_1KB);
}

TEST(ArenaAllocatorTestSuite, MemoryAllocation1) {
    ArenaAllocator arena(BEBONE_MEMORY_BYTES_1KB);

    int* mem = static_cast<int*>(arena.alloc(sizeof(int)));
    *mem = 69;

    ASSERT_EQ(*mem, 69);
}

TEST(ArenaAllocatorTestSuite, MemoryAllocation2) {
    ArenaAllocator arena(BEBONE_MEMORY_BYTES_1KB);

    int* mem_int = static_cast<int*>(arena.alloc(sizeof(int)));
    *mem_int = 69;

    struct Data{ int data[16]; };

    Data* mem_data = static_cast<Data*>(arena.alloc(sizeof(Data)));
    *mem_data = Data();

    ASSERT_EQ(*mem_int, 69);
}

TEST(ArenaAllocatorTestSuite, MemoryAllocation3) {
    ArenaAllocator arena(BEBONE_MEMORY_BYTES_1KB);

    {
        int* mem_int = static_cast<int*>(arena.alloc(sizeof(int)));
        *mem_int = 420;
    }

    arena.clear();

    int* mem_int = static_cast<int*>(arena.alloc(sizeof(int)));
    *mem_int = 69;

    ASSERT_EQ(*mem_int, 69);
}

TEST(ArenaAllocatorTestSuite, MemoryAllocation4) {
    ArenaAllocator arena(sizeof(char));

    char* mem_char = static_cast<char*>(arena.alloc(sizeof(char)));
    *mem_char = 25;
    ASSERT_EQ(*mem_char, 25);

    void* ptr = arena.alloc(sizeof(size_t));
    ASSERT_EQ(ptr, nullptr);
}