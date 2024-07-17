#include "bebone/core/core.h"
#include "gtest/gtest.h"

using namespace bebone::core;

TEST(Matrix3x3Math, Initialization) {
    Matrix3x3f a(4, 3, 1,
                 2, 1, 0,
                 5, 3, 2);

    ASSERT_EQ(a(0, 0), 4);
    ASSERT_EQ(a(0, 1), 3);
    ASSERT_EQ(a(0, 2), 1);
    ASSERT_EQ(a(1, 0), 2);
    ASSERT_EQ(a(1, 1), 1);
    ASSERT_EQ(a(1, 2), 0);
    ASSERT_EQ(a(2, 0), 5);
    ASSERT_EQ(a(2, 1), 3);
    ASSERT_EQ(a(2, 2), 2);

    Matrix3x3f b(5, 6, 3,
                 7, 8, 2,
                 6, 3, 1);

    ASSERT_EQ(b(0, 0), 5);
    ASSERT_EQ(b(0, 1), 6);
    ASSERT_EQ(b(0, 2), 3);
    ASSERT_EQ(b(1, 0), 7);
    ASSERT_EQ(b(1, 1), 8);
    ASSERT_EQ(b(1, 2), 2);
    ASSERT_EQ(b(2, 0), 6);
    ASSERT_EQ(b(2, 1), 3);
    ASSERT_EQ(b(2, 2), 1);
}

TEST(Matrix3x3Math, MatrixAddition) {
    Matrix3x3f a(1, 2, 3,
                 4, 5, 6,
                 7, 8, 9);

    Matrix3x3f b(3, 4, 1,
                 5, 6, 0,
                 4, 2, 1);

    Matrix3x3f c(3, 1, 4,
                 5, 4, 3,
                 6, 0, 0);

    Matrix3x3f result = a + b;
    ASSERT_TRUE(result == Matrix3x3f(4, 6, 4,
                                     9, 11, 6,
                                     11, 10, 10));
    result = b + c;
    ASSERT_TRUE(result == Matrix3x3f(6, 5, 5,
                                     10, 10, 3,
                                     10, 2, 1));
}

TEST(Matrix3x3Math, MatrixSubtraction) {
    Matrix3x3f a(1, 2, 3,
                 4, 5, 6,
                 7, 8, 9);

    Matrix3x3f b(3, 4, 1,
                 5, 6, 0,
                 4, 2, 1);

    Matrix3x3f c(3, 1, 4,
                 5, 4, 3,
                 6, 0, 0);

    Matrix3x3f result = a - b;
    ASSERT_TRUE(result == Matrix3x3f(-2, -2, 2,
                                     -1, -1, 6,
                                     3, 6, 8));
    result = a - c;
    ASSERT_TRUE(result == Matrix3x3f(-2, 1, -1,
                                     -1, 1, 3,
                                     1, 8, 9));
}

TEST(Matrix3x3Math, MatrixMultiplication) {
    Matrix3x3f a(1, 2, 3,
                 4, 5, 6,
                 7, 8, 9);

    Matrix3x3f b(3, 4, 1,
                 5, 6, 0,
                 4, 2, 1);

    Matrix3x3f c(3, 1, 4,
                 5, 4, 3,
                 6, 0, 0);

    Matrix3x3f result = a * b;
    ASSERT_TRUE(result == Matrix3x3f(25, 22, 4,
                                     61, 58, 10,
                                     97, 94, 16));
    result = b * a;
    ASSERT_TRUE(result == Matrix3x3f(26, 34, 42,
                                     29, 40, 51,
                                     19, 26, 33));
    result = b * c;
    ASSERT_TRUE(result == Matrix3x3f(35, 19, 24,
                                     45, 29, 38,
                                     28, 12, 22));
    result = c * b;
    ASSERT_TRUE(result == Matrix3x3f(30, 26, 7,
                                     47, 50, 8,
                                     18, 24, 6));
}

TEST(Matrix3x3Math, ScalarAddition) {
    Matrix3x3f a(1, 2, 3,
                 4, 5, 6,
                 7, 8, 9);

    Matrix3x3f b(3, 4, 1,
                 5, 6, 0,
                 4, 2, 1);

    Matrix3x3f result = a + 4;
    ASSERT_TRUE(result == Matrix3x3f(5, 6, 7,
                                     8, 9, 10,
                                     11, 12, 13));
    result = b + 7;
    ASSERT_TRUE(result == Matrix3x3f(10, 11, 8,
                                     12, 13, 7,
                                     11, 9, 8));
}

TEST(Matrix3x3Math, ScalarSubtraction) {
    Matrix3x3f a(1, 2, 3,
                 4, 5, 6,
                 7, 8, 9);

    Matrix3x3f b(3, 4, 1,
                 5, 6, 0,
                 4, 2, 1);

    Matrix3x3f result = a - 4;
    ASSERT_TRUE(result == Matrix3x3f(-3, -2, -1,
                                     0, 1, 2,
                                     3, 4, 5));
    result = b - 7;
    ASSERT_TRUE(result == Matrix3x3f(-4, -3, -6,
                                     -2, -1, -7,
                                     -3, -5, -6));
}

TEST(Matrix3x3Math, ScalarMultiplication) {
    Matrix3x3f a(1, 2, 3,
                 4, 5, 6,
                 7, 8, 9);

    Matrix3x3f b(3, 4, 1,
                 5, 6, 0,
                 4, 2, 1);

    Matrix3x3f result = a * 4;
    ASSERT_TRUE(result == Matrix3x3f(4, 8, 12,
                                     16, 20, 24,
                                     28, 32, 36));
    result = b * 7;
    ASSERT_TRUE(result == Matrix3x3f(21, 28, 7,
                                     35, 42, 0,
                                     28, 14, 7));
}

TEST(Matrix3x3Math, ScalarDivision) {
    Matrix3x3f a(25, 0, 10,
                 15, 5, 30,
                 35, 100, 45);

    Matrix3x3f b(6, 4, 2,
                 0, 8, 16,
                 20, 10, 8);

    Matrix3x3f result = a / 5;
    ASSERT_TRUE(result == Matrix3x3f(5, 0, 2,
                                     3, 1, 6,
                                     7, 20, 9));
    result = b / 2;
    ASSERT_TRUE(result == Matrix3x3f(3, 2, 1,
                                     0, 4, 8,
                                     10, 5, 4));
}

TEST(Matrix3x3Functions, Transpose) {
    Matrix3x3f a(1, 2, 3,
                 4, 5, 6,
                 7, 8, 9);

    Matrix3x3f b(3, 4, 1,
                 5, 6, 0,
                 4, 2, 1);

    Matrix3x3f result = a.transpose();
    ASSERT_TRUE(result == Matrix3x3f(1, 4, 7,
                                     2, 5, 8,
                                     3, 6, 9));
    result = b.transpose();
    ASSERT_TRUE(result == Matrix3x3f(3, 5, 4,
                                     4, 6, 2,
                                     1, 0, 1));
}

TEST(Matrix3x3Functions, Inverse) {
    Matrix3x3f a(5, 6, 3,
                 4, 5, 6,
                 7, 8, 9);

    Matrix3x3f b(3, 4, 1,
                 5, 6, 0,
                 4, 2, 1);

    Matrix3x3f result = a.inverse();
    ASSERT_FLOAT_EQ(result(0, 0), -0.25f);
    ASSERT_FLOAT_EQ(result(0, 1), -2.5f);
    ASSERT_FLOAT_EQ(result(0, 2), 1.75f);
    ASSERT_FLOAT_EQ(result(1, 0), 0.5f);
    ASSERT_FLOAT_EQ(result(1, 1), 2.0f);
    ASSERT_FLOAT_EQ(result(1, 2), -1.5f);
    ASSERT_FLOAT_EQ(result(2, 0), -0.25f);
    ASSERT_FLOAT_EQ(result(2, 1), 0.1666667f);
    ASSERT_FLOAT_EQ(result(2, 2), 0.08333333f);

    result = b.inverse();
    ASSERT_FLOAT_EQ(result(0, 0), -0.375f);
    ASSERT_FLOAT_EQ(result(0, 1), 0.125f);
    ASSERT_FLOAT_EQ(result(0, 2), 0.375f);
    ASSERT_FLOAT_EQ(result(1, 0), 0.3125f);
    ASSERT_FLOAT_EQ(result(1, 1), 0.0625f);
    ASSERT_FLOAT_EQ(result(1, 2), -0.3125f);
    ASSERT_FLOAT_EQ(result(2, 0), 0.875f);
    ASSERT_FLOAT_EQ(result(2, 1), -0.625f);
    ASSERT_FLOAT_EQ(result(2, 2), 0.125f);
}