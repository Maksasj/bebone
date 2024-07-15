#include "bebone/core/core.h"
#include "gtest/gtest.h"

TEST(MatrixMultiplicationSuite, First) {
    using namespace bebone::core;

    Mat4f a = {{5, 2, 6, 1, 0, 6, 2, 0, 3, 8, 1, 4, 1, 8, 5, 6}};
    Mat4f b = {{7, 5, 8, 0, 1, 8, 2, 6, 9, 4, 3, 8, 5, 3, 7, 9}};

    Mat4f c = {{96, 68, 69, 69, 24, 56, 18, 52, 58, 95, 71, 92, 90, 107, 81, 142}};

    ASSERT_EQ(a * b, c);
}

TEST(MatrixMultiplicationSuite, Second) {
    using namespace bebone::core;
    Mat4f a = {{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16}};
    Mat4f b = {{17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32}};

    Mat4f c = {{250, 260, 270, 280, 618, 644, 670, 696, 986, 1028, 1070, 1112, 1354, 1412, 1470, 1528}};

    ASSERT_EQ(a * b, c);
}
