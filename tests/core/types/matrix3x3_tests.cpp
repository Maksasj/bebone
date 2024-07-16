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
    ASSERT_EQ(result(0, 0), 4);
    ASSERT_EQ(result(0, 1), 6);
    ASSERT_EQ(result(0, 2), 4);
    ASSERT_EQ(result(1, 0), 9);
    ASSERT_EQ(result(1, 1), 11);
    ASSERT_EQ(result(1, 2), 6);
    ASSERT_EQ(result(2, 0), 11);
    ASSERT_EQ(result(2, 1), 10);
    ASSERT_EQ(result(2, 2), 10);

    result = b + c;
    ASSERT_EQ(result(0, 0), 6);
    ASSERT_EQ(result(0, 1), 5);
    ASSERT_EQ(result(0, 2), 5);
    ASSERT_EQ(result(1, 0), 10);
    ASSERT_EQ(result(1, 1), 10);
    ASSERT_EQ(result(1, 2), 3);
    ASSERT_EQ(result(2, 0), 10);
    ASSERT_EQ(result(2, 1), 2);
    ASSERT_EQ(result(2, 2), 1);
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
    ASSERT_EQ(result(0, 0), -2);
    ASSERT_EQ(result(0, 1), -2);
    ASSERT_EQ(result(0, 2), 2);
    ASSERT_EQ(result(1, 0), -1);
    ASSERT_EQ(result(1, 1), -1);
    ASSERT_EQ(result(1, 2), 6);
    ASSERT_EQ(result(2, 0), 3);
    ASSERT_EQ(result(2, 1), 6);
    ASSERT_EQ(result(2, 2), 8);

    result = a - c;
    ASSERT_EQ(result(0, 0), -2);
    ASSERT_EQ(result(0, 1), 1);
    ASSERT_EQ(result(0, 2), -1);
    ASSERT_EQ(result(1, 0), -1);
    ASSERT_EQ(result(1, 1), 1);
    ASSERT_EQ(result(1, 2), 3);
    ASSERT_EQ(result(2, 0), 1);
    ASSERT_EQ(result(2, 1), 8);
    ASSERT_EQ(result(2, 2), 9);
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
    ASSERT_EQ(result(0, 0), 25);
    ASSERT_EQ(result(0, 1), 22);
    ASSERT_EQ(result(0, 2), 4);
    ASSERT_EQ(result(1, 0), 61);
    ASSERT_EQ(result(1, 1), 58);
    ASSERT_EQ(result(1, 2), 10);
    ASSERT_EQ(result(2, 0), 97);
    ASSERT_EQ(result(2, 1), 94);
    ASSERT_EQ(result(2, 2), 16);

    result = b * a;
    ASSERT_EQ(result(0, 0), 26);
    ASSERT_EQ(result(0, 1), 34);
    ASSERT_EQ(result(0, 2), 42);
    ASSERT_EQ(result(1, 0), 29);
    ASSERT_EQ(result(1, 1), 40);
    ASSERT_EQ(result(1, 2), 51);
    ASSERT_EQ(result(2, 0), 19);
    ASSERT_EQ(result(2, 1), 26);
    ASSERT_EQ(result(2, 2), 33);

    result = b * c;
    ASSERT_EQ(result(0, 0), 35);
    ASSERT_EQ(result(0, 1), 19);
    ASSERT_EQ(result(0, 2), 24);
    ASSERT_EQ(result(1, 0), 45);
    ASSERT_EQ(result(1, 1), 29);
    ASSERT_EQ(result(1, 2), 38);
    ASSERT_EQ(result(2, 0), 28);
    ASSERT_EQ(result(2, 1), 12);
    ASSERT_EQ(result(2, 2), 22);

    result = c * b;
    ASSERT_EQ(result(0, 0), 30);
    ASSERT_EQ(result(0, 1), 26);
    ASSERT_EQ(result(0, 2), 7);
    ASSERT_EQ(result(1, 0), 47);
    ASSERT_EQ(result(1, 1), 50);
    ASSERT_EQ(result(1, 2), 8);
    ASSERT_EQ(result(2, 0), 18);
    ASSERT_EQ(result(2, 1), 24);
    ASSERT_EQ(result(2, 2), 6);
}

TEST(Matrix3x3Math, ScalarAddition) {
    Matrix3x3f a(1, 2, 3,
                 4, 5, 6,
                 7, 8, 9);

    Matrix3x3f b(3, 4, 1,
                 5, 6, 0,
                 4, 2, 1);

    Matrix3x3f result = a + 4;

    ASSERT_EQ(result(0, 0), 5);
    ASSERT_EQ(result(0, 1), 6);
    ASSERT_EQ(result(0, 2), 7);
    ASSERT_EQ(result(1, 0), 8);
    ASSERT_EQ(result(1, 1), 9);
    ASSERT_EQ(result(1, 2), 10);
    ASSERT_EQ(result(2, 0), 11);
    ASSERT_EQ(result(2, 1), 12);
    ASSERT_EQ(result(2, 2), 13);

    result = b + 7;
    ASSERT_EQ(result(0, 0), 10);
    ASSERT_EQ(result(0, 1), 11);
    ASSERT_EQ(result(0, 2), 8);
    ASSERT_EQ(result(1, 0), 12);
    ASSERT_EQ(result(1, 1), 13);
    ASSERT_EQ(result(1, 2), 7);
    ASSERT_EQ(result(2, 0), 11);
    ASSERT_EQ(result(2, 1), 9);
    ASSERT_EQ(result(2, 2), 8);
}

TEST(Matrix3x3Math, ScalarSubtraction) {
    Matrix3x3f a(1, 2, 3,
                 4, 5, 6,
                 7, 8, 9);

    Matrix3x3f b(3, 4, 1,
                 5, 6, 0,
                 4, 2, 1);

    Matrix3x3f result = a - 4;

    ASSERT_EQ(result(0, 0), -3);
    ASSERT_EQ(result(0, 1), -2);
    ASSERT_EQ(result(0, 2), -1);
    ASSERT_EQ(result(1, 0), 0);
    ASSERT_EQ(result(1, 1), 1);
    ASSERT_EQ(result(1, 2), 2);
    ASSERT_EQ(result(2, 0), 3);
    ASSERT_EQ(result(2, 1), 4);
    ASSERT_EQ(result(2, 2), 5);

    result = b - 7;
    ASSERT_EQ(result(0, 0), -4);
    ASSERT_EQ(result(0, 1), -3);
    ASSERT_EQ(result(0, 2), -6);
    ASSERT_EQ(result(1, 0), -2);
    ASSERT_EQ(result(1, 1), -1);
    ASSERT_EQ(result(1, 2), -7);
    ASSERT_EQ(result(2, 0), -3);
    ASSERT_EQ(result(2, 1), -5);
    ASSERT_EQ(result(2, 2), -6);
}

TEST(Matrix3x3Math, ScalarMultiplication) {
    Matrix3x3f a(1, 2, 3,
                 4, 5, 6,
                 7, 8, 9);

    Matrix3x3f b(3, 4, 1,
                 5, 6, 0,
                 4, 2, 1);

    Matrix3x3f result = a * 4;

    ASSERT_EQ(result(0, 0), 4);
    ASSERT_EQ(result(0, 1), 8);
    ASSERT_EQ(result(0, 2), 12);
    ASSERT_EQ(result(1, 0), 16);
    ASSERT_EQ(result(1, 1), 20);
    ASSERT_EQ(result(1, 2), 24);
    ASSERT_EQ(result(2, 0), 28);
    ASSERT_EQ(result(2, 1), 32);
    ASSERT_EQ(result(2, 2), 36);

    result = b * 7;
    ASSERT_EQ(result(0, 0), 21);
    ASSERT_EQ(result(0, 1), 28);
    ASSERT_EQ(result(0, 2), 7);
    ASSERT_EQ(result(1, 0), 35);
    ASSERT_EQ(result(1, 1), 42);
    ASSERT_EQ(result(1, 2), 0);
    ASSERT_EQ(result(2, 0), 28);
    ASSERT_EQ(result(2, 1), 14);
    ASSERT_EQ(result(2, 2), 7);
}

TEST(Matrix3x3Math, ScalarDivision) {
    Matrix3x3f a(25, 0, 10,
                 15, 5, 30,
                 35, 100, 45);

    Matrix3x3f b(6, 4, 2,
                 0, 8, 16,
                 20, 10, 8);

    Matrix3x3f result = a / 5;

    ASSERT_EQ(result(0, 0), 5);
    ASSERT_EQ(result(0, 1), 0);
    ASSERT_EQ(result(0, 2), 2);
    ASSERT_EQ(result(1, 0), 3);
    ASSERT_EQ(result(1, 1), 1);
    ASSERT_EQ(result(1, 2), 6);
    ASSERT_EQ(result(2, 0), 7);
    ASSERT_EQ(result(2, 1), 20);
    ASSERT_EQ(result(2, 2), 9);

    result = b / 2;
    ASSERT_EQ(result(0, 0), 3);
    ASSERT_EQ(result(0, 1), 2);
    ASSERT_EQ(result(0, 2), 1);
    ASSERT_EQ(result(1, 0), 0);
    ASSERT_EQ(result(1, 1), 4);
    ASSERT_EQ(result(1, 2), 8);
    ASSERT_EQ(result(2, 0), 10);
    ASSERT_EQ(result(2, 1), 5);
    ASSERT_EQ(result(2, 2), 4);
}

TEST(Matrix3x3Functions, Transpose) {
    Matrix3x3f a(1, 2, 3,
                 4, 5, 6,
                 7, 8, 9);

    Matrix3x3f b(3, 4, 1,
                 5, 6, 0,
                 4, 2, 1);

    Matrix3x3f result = a.transpose();
    ASSERT_EQ(result(0, 0), 1);
    ASSERT_EQ(result(0, 1), 4);
    ASSERT_EQ(result(0, 2), 7);
    ASSERT_EQ(result(1, 0), 2);
    ASSERT_EQ(result(1, 1), 5);
    ASSERT_EQ(result(1, 2), 8);
    ASSERT_EQ(result(2, 0), 3);
    ASSERT_EQ(result(2, 1), 6);
    ASSERT_EQ(result(2, 2), 9);

    result = b.transpose();
    ASSERT_EQ(result(0, 0), 3);
    ASSERT_EQ(result(0, 1), 5);
    ASSERT_EQ(result(0, 2), 4);
    ASSERT_EQ(result(1, 0), 4);
    ASSERT_EQ(result(1, 1), 6);
    ASSERT_EQ(result(1, 2), 2);
    ASSERT_EQ(result(2, 0), 1);
    ASSERT_EQ(result(2, 1), 0);
    ASSERT_EQ(result(2, 2), 1);
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