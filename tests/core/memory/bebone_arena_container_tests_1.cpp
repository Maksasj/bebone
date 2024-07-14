#include "bebone/core/core.h"
#include "gtest/gtest.h"

using namespace bebone::core;

TEST(ArenaContainerTestSuite, First) {
    ArenaContainer container(BEBONE_MEMORY_BYTES_1KB);

    int* e1 = static_cast<int*>(container.alloc(sizeof(int)));
    int* e2 = static_cast<int*>(container.alloc(sizeof(int)));
    int* e3 = static_cast<int*>(container.alloc(sizeof(int)));

    *e1 = 16;
    *e2 = 32;
    *e3 = 64;

    int* ee1 = static_cast<int*>(container.at(0));
    int* ee2 = static_cast<int*>(container.at(1));
    int* ee3 = static_cast<int*>(container.at(2));

    ASSERT_EQ(*ee1, *e1);
    ASSERT_EQ(*ee2, *e2);
    ASSERT_EQ(*ee3, *e3);

    ASSERT_EQ(container.size(), 3);
}

TEST(ArenaContainerTestSuite, Second) {
    ArenaContainer container(BEBONE_MEMORY_BYTES_1KB * 256);

    for(int i = 0; i < 100; ++i) {
        int* e = static_cast<int*>(container.alloc(sizeof(int)));
        *e = i;

        ASSERT_EQ(container.size(), static_cast<size_t>(i + 1));
    }

    for(int i = 0; i < 100; ++i) {
        int* e = static_cast<int*>(container.at(i));
        ASSERT_EQ(*e, i);
    }

    ASSERT_EQ(container.size(), 100);
}

TEST(ArenaContainerTestSuite, Third) {
    ArenaContainer container(BEBONE_MEMORY_BYTES_1KB * 256);

    for(int i = 0; i < 100; ++i) {
        int* e = static_cast<int*>(container.alloc(sizeof(int)));
        *e = i;

        ASSERT_EQ(container.size(), static_cast<size_t>(i + 1));
    }

    container.clear();

    ASSERT_EQ(container.size(), 0);
}