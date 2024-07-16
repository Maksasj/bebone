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
    ASSERT_EQ(result(0, 0), 4);
    ASSERT_EQ(result(0, 1), 6);
    ASSERT_EQ(result(1, 0), 8);
    ASSERT_EQ(result(1, 1), 10);

    result = b + c;
    ASSERT_EQ(result(0, 0), 6);
    ASSERT_EQ(result(0, 1), 5);
    ASSERT_EQ(result(1, 0), 10);
    ASSERT_EQ(result(1, 1), 10);
}

TEST(Matrix2x2Math, MatrixSubtraction) {
    Matrix2x2f a(15, 7,
                 3, 8);

    Matrix2x2f b(0, 1,
                 4, 3);

    Matrix2x2f c(6, 4,
                 3, 5);

    Matrix2x2f result = a - b;
    ASSERT_EQ(result(0, 0), 15);
    ASSERT_EQ(result(0, 1), 6);
    ASSERT_EQ(result(1, 0), -1);
    ASSERT_EQ(result(1, 1), 5);

    result = a - c;
    ASSERT_EQ(result(0, 0), 9);
    ASSERT_EQ(result(0, 1), 3);
    ASSERT_EQ(result(1, 0), 0);
    ASSERT_EQ(result(1, 1), 3);
}

TEST(Matrix2x2Math, MatrixMultiplication) {
    Matrix2x2f a(15, 7,
                 3, 8);

    Matrix2x2f b(0, 1,
                 4, 3);

    Matrix2x2f c(6, 4,
                 3, 5);

    Matrix2x2f result = a * b;
    ASSERT_EQ(result(0, 0), 28);
    ASSERT_EQ(result(0, 1), 36);
    ASSERT_EQ(result(1, 0), 32);
    ASSERT_EQ(result(1, 1), 27);

    result = b * a;
    ASSERT_EQ(result(0, 0), 3);
    ASSERT_EQ(result(0, 1), 8);
    ASSERT_EQ(result(1, 0), 69);
    ASSERT_EQ(result(1, 1), 52);

    result = b * c;
    ASSERT_EQ(result(0, 0), 3);
    ASSERT_EQ(result(0, 1), 5);
    ASSERT_EQ(result(1, 0), 33);
    ASSERT_EQ(result(1, 1), 31);

    result = c * b;
    ASSERT_EQ(result(0, 0), 16);
    ASSERT_EQ(result(0, 1), 18);
    ASSERT_EQ(result(1, 0), 20);
    ASSERT_EQ(result(1, 1), 18);
}

TEST(Matrix2x2Math, ScalarAddition) {
    Matrix2x2f a(5, 3,
                 2, 5);

    Matrix2x2f b(6, 2,
                 4, 0);

    Matrix2x2f result = a + 4;

    ASSERT_EQ(result(0, 0), 9);
    ASSERT_EQ(result(0, 1), 7);
    ASSERT_EQ(result(1, 0), 6);
    ASSERT_EQ(result(1, 1), 9);

    result = b + 7;
    ASSERT_EQ(result(0, 0), 13);
    ASSERT_EQ(result(0, 1), 9);
    ASSERT_EQ(result(1, 0), 11);
    ASSERT_EQ(result(1, 1), 7);
}

TEST(Matrix2x2Math, ScalarSubtraction) {
    Matrix2x2f a(5, 3,
                 2, 5);

    Matrix2x2f b(6, 2,
                 4, 0);

    Matrix2x2f result = a - 4;

    ASSERT_EQ(result(0, 0), 1);
    ASSERT_EQ(result(0, 1), -1);
    ASSERT_EQ(result(1, 0), -2);
    ASSERT_EQ(result(1, 1), 1);

    result = b - 7;
    ASSERT_EQ(result(0, 0), -1);
    ASSERT_EQ(result(0, 1), -5);
    ASSERT_EQ(result(1, 0), -3);
    ASSERT_EQ(result(1, 1), -7);
}

TEST(Matrix2x2Math, ScalarMultiplication) {
    Matrix2x2f a(5, 3,
                 2, 5);

    Matrix2x2f b(6, 2,
                 4, 0);

    Matrix2x2f result = a * 4;

    ASSERT_EQ(result(0, 0), 20);
    ASSERT_EQ(result(0, 1), 12);
    ASSERT_EQ(result(1, 0), 8);
    ASSERT_EQ(result(1, 1), 20);

    result = b * 7;
    ASSERT_EQ(result(0, 0), 42);
    ASSERT_EQ(result(0, 1), 14);
    ASSERT_EQ(result(1, 0), 28);
    ASSERT_EQ(result(1, 1), 0);
}

TEST(Matrix2x2Math, ScalarDivision) {
    Matrix2x2f a(5, 25,
                 10, 5);

    Matrix2x2f b(6, 2,
                 4, 0);

    Matrix2x2f result = a / 5;

    ASSERT_EQ(result(0, 0), 1);
    ASSERT_EQ(result(0, 1), 5);
    ASSERT_EQ(result(1, 0), 2);
    ASSERT_EQ(result(1, 1), 1);

    result = b / 2;
    ASSERT_EQ(result(0, 0), 3);
    ASSERT_EQ(result(0, 1), 1);
    ASSERT_EQ(result(1, 0), 2);
    ASSERT_EQ(result(1, 1), 0);
}

TEST(Matrix2x2Functions, Transpose) {
    Matrix2x2f a(1, 2,
                 3, 4);

    Matrix2x2f b(47, 4,
                 8, 0);

    Matrix2x2f result = a.transpose();
    ASSERT_EQ(result(0, 0), 1);
    ASSERT_EQ(result(0, 1), 3);
    ASSERT_EQ(result(1, 0), 2);
    ASSERT_EQ(result(1, 1), 4);

    result = b.transpose();
    ASSERT_EQ(result(0, 0), 47);
    ASSERT_EQ(result(0, 1), 8);
    ASSERT_EQ(result(1, 0), 4);
    ASSERT_EQ(result(1, 1), 0);
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