#include "bebone/core/core.h"
#include "gtest/gtest.h"

using namespace bebone::core;

TEST(Matrix2x2Math, Initialization) {
    Matrix2x2f a(4, 3,
                 2, 1);

    ASSERT_EQ(a(0, 0), 4);
    ASSERT_EQ(a(0, 1), 3);
    ASSERT_EQ(a(1, 0), 2);
    ASSERT_EQ(a(1, 1), 1);

    Matrix2x2f b(5, 6,
                 7, 8);

    ASSERT_EQ(b(0, 0), 5);
    ASSERT_EQ(b(0, 1), 6);
    ASSERT_EQ(b(1, 0), 7);
    ASSERT_EQ(b(1, 1), 8);
}

TEST(Matrix2x2Math, MatrixAddition) {
    Matrix2x2f a(1, 2,
                 3, 4);

    Matrix2x2f b(3, 4,
                 5, 6);

    Matrix2x2f c(3, 1,
                 5, 4);

    Matrix2x2f result = a + b;
    ASSERT_TRUE(result == Matrix2x2f(4, 6,
                                     8, 10));

    result = b + c;
    ASSERT_TRUE(result == Matrix2x2f(6, 5,
                                     10, 10));
}

TEST(Matrix2x2Math, MatrixSubtraction) {
    Matrix2x2f a(15, 7,
                 3, 8);

    Matrix2x2f b(0, 1,
                 4, 3);

    Matrix2x2f c(6, 4,
                 3, 5);

    Matrix2x2f result = a - b;
    ASSERT_TRUE(result == Matrix2x2f(15, 6,
                                     -1, 5));
    result = a - c;
    ASSERT_TRUE(result == Matrix2x2f(9, 3,
                                     0, 3));
}

TEST(Matrix2x2Math, MatrixMultiplication) {
    Matrix2x2f a(15, 7,
                 3, 8);

    Matrix2x2f b(0, 1,
                 4, 3);

    Matrix2x2f c(6, 4,
                 3, 5);

    Matrix2x2f result = a * b;
    ASSERT_TRUE(result == Matrix2x2f(28, 36,
                                     32, 27));
    result = b * a;
    ASSERT_TRUE(result == Matrix2x2f(3, 8,
                                     69, 52));
    result = b * c;
    ASSERT_TRUE(result == Matrix2x2f(3, 5,
                                     33, 31));
    result = c * b;
    ASSERT_TRUE(result == Matrix2x2f(16, 18,
                                     20, 18));
}

TEST(Matrix2x2Math, ScalarAddition) {
    Matrix2x2f a(5, 3,
                 2, 5);

    Matrix2x2f b(6, 2,
                 4, 0);

    Matrix2x2f result = a + 4;
    ASSERT_TRUE(result == Matrix2x2f(9, 7,
                                     6, 9));
    result = b + 7;
    ASSERT_TRUE(result == Matrix2x2f(13, 9,
                                     11, 7));
}

TEST(Matrix2x2Math, ScalarSubtraction) {
    Matrix2x2f a(5, 3,
                 2, 5);

    Matrix2x2f b(6, 2,
                 4, 0);

    Matrix2x2f result = a - 4;
    ASSERT_TRUE(result == Matrix2x2f(1, -1,
                                     -2, 1));
    result = b - 7;
    ASSERT_TRUE(result == Matrix2x2f(-1, -5,
                                     -3, -7));
}

TEST(Matrix2x2Math, ScalarMultiplication) {
    Matrix2x2f a(5, 3,
                 2, 5);

    Matrix2x2f b(6, 2,
                 4, 0);

    Matrix2x2f result = a * 4;
    ASSERT_TRUE(result == Matrix2x2f(20, 12,
                                     8, 20));
    result = b * 7;
    ASSERT_TRUE(result == Matrix2x2f(42, 14,
                                     28, 0));
}

TEST(Matrix2x2Math, ScalarDivision) {
    Matrix2x2f a(5, 25,
                 10, 5);

    Matrix2x2f b(6, 2,
                 4, 0);

    Matrix2x2f result = a / 5;
    ASSERT_TRUE(result == Matrix2x2f(1, 5,
                                     2, 1));
    result = b / 2;
    ASSERT_TRUE(result == Matrix2x2f(3, 1,
                                     2, 0));
}

TEST(Matrix2x2Functions, Transpose) {
    Matrix2x2f a(1, 2,
                 3, 4);

    Matrix2x2f b(47, 4,
                 8, 0);

    Matrix2x2f result = a.transpose();
    ASSERT_TRUE(result == Matrix2x2f(1, 3,
                                     2, 4));
    result = b.transpose();
    ASSERT_TRUE(result == Matrix2x2f(47, 8,
                                     4, 0));
}

TEST(Matrix2x2Functions, Inverse) {
    Matrix2x2f a(5, 2,
                 4, 10);

    Matrix2x2f b(4, 4,
                 0, 2);

    Matrix2x2f result = a.inverse();
    ASSERT_FLOAT_EQ(result(0, 0), 0.2380952f);
    ASSERT_FLOAT_EQ(result(0, 1), -0.047619049f);
    ASSERT_FLOAT_EQ(result(1, 0), -0.095238097f);
    ASSERT_FLOAT_EQ(result(1, 1), 0.1190476f);

    result = b.inverse();
    ASSERT_FLOAT_EQ(result(0, 0), 0.25f);
    ASSERT_FLOAT_EQ(result(0, 1), -0.5f);
    ASSERT_FLOAT_EQ(result(1, 0), 0);
    ASSERT_FLOAT_EQ(result(1, 1), 0.5f);
}