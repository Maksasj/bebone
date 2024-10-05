#include "bebone/core/core.h"
#include "gtest/gtest.h"

using namespace bebone::core;

TEST(Matrix3x3Math, Initialization) {
    // Arrange
    Matrix3x3f a(4, 3, 1,
                 2, 1, 0,
                 5, 3, 2);

    Matrix3x3f b(5, 6, 3,
                 7, 8, 2,
                 6, 3, 1);
    // Act

    // Assert
    ASSERT_EQ(a(0, 0), 4);
    ASSERT_EQ(a(0, 1), 3);
    ASSERT_EQ(a(0, 2), 1);
    ASSERT_EQ(a(1, 0), 2);
    ASSERT_EQ(a(1, 1), 1);
    ASSERT_EQ(a(1, 2), 0);
    ASSERT_EQ(a(2, 0), 5);
    ASSERT_EQ(a(2, 1), 3);
    ASSERT_EQ(a(2, 2), 2);

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
    // Arrange
    Matrix3x3f a(1, 2, 3,
                 4, 5, 6,
                 7, 8, 9);

    Matrix3x3f b(3, 4, 1,
                 5, 6, 0,
                 4, 2, 1);

    Matrix3x3f c(3, 1, 4,
                 5, 4, 3,
                 6, 0, 0);

    // Act
    Matrix3x3f result0 = a + b;
    Matrix3x3f result1 = b + c;

    // Assert
    ASSERT_TRUE(result0 == Matrix3x3f(4, 6, 4,
                                     9, 11, 6,
                                     11, 10, 10));

    ASSERT_TRUE(result1 == Matrix3x3f(6, 5, 5,
                                     10, 10, 3,
                                     10, 2, 1));
}

TEST(Matrix3x3Math, MatrixSubtraction) {
    // Arrange
    Matrix3x3f a(1, 2, 3,
                 4, 5, 6,
                 7, 8, 9);

    Matrix3x3f b(3, 4, 1,
                 5, 6, 0,
                 4, 2, 1);

    Matrix3x3f c(3, 1, 4,
                 5, 4, 3,
                 6, 0, 0);

    // Act
    Matrix3x3f result0 = a - b;
    Matrix3x3f result1 = a - c;

    // Assert
    ASSERT_TRUE(result0 == Matrix3x3f(-2, -2, 2,
                                     -1, -1, 6,
                                     3, 6, 8));

    ASSERT_TRUE(result1 == Matrix3x3f(-2, 1, -1,
                                     -1, 1, 3,
                                     1, 8, 9));
}

TEST(Matrix3x3Math, MatrixMultiplication) {
    // Arrange
    Matrix3x3f a(1, 2, 3,
                 4, 5, 6,
                 7, 8, 9);

    Matrix3x3f b(3, 4, 1,
                 5, 6, 0,
                 4, 2, 1);

    Matrix3x3f c(3, 1, 4,
                 5, 4, 3,
                 6, 0, 0);

    // Act
    Matrix3x3f result0 = a * b;
    Matrix3x3f result1 = b * a;
    Matrix3x3f result2 = b * c;
    Matrix3x3f result3 = c * b;

    // Assert
    ASSERT_TRUE(result0 == Matrix3x3f(25, 22, 4,
                                     61, 58, 10,
                                     97, 94, 16));

    ASSERT_TRUE(result1 == Matrix3x3f(26, 34, 42,
                                     29, 40, 51,
                                     19, 26, 33));

    ASSERT_TRUE(result2 == Matrix3x3f(35, 19, 24,
                                     45, 29, 38,
                                     28, 12, 22));

    ASSERT_TRUE(result3 == Matrix3x3f(30, 26, 7,
                                     47, 50, 8,
                                     18, 24, 6));
}

TEST(Matrix3x3Math, ScalarAddition) {
    // Arrange
    Matrix3x3f a(1, 2, 3,
                 4, 5, 6,
                 7, 8, 9);

    Matrix3x3f b(3, 4, 1,
                 5, 6, 0,
                 4, 2, 1);

    // Act
    Matrix3x3f result0 = a + 4;
    Matrix3x3f result1 = b + 7;

    // Assert
    ASSERT_TRUE(result0 == Matrix3x3f(5, 6, 7,
                                     8, 9, 10,
                                     11, 12, 13));

    ASSERT_TRUE(result1 == Matrix3x3f(10, 11, 8,
                                     12, 13, 7,
                                     11, 9, 8));
}

TEST(Matrix3x3Math, ScalarSubtraction) {
    // Arrange
    Matrix3x3f a(1, 2, 3,
                 4, 5, 6,
                 7, 8, 9);

    Matrix3x3f b(3, 4, 1,
                 5, 6, 0,
                 4, 2, 1);

    // Act
    Matrix3x3f result0 = a - 4;
    Matrix3x3f result1 = b - 7;

    // Assert
    ASSERT_TRUE(result0 == Matrix3x3f(-3, -2, -1,
                                     0, 1, 2,
                                     3, 4, 5));

    ASSERT_TRUE(result1 == Matrix3x3f(-4, -3, -6,
                                     -2, -1, -7,
                                     -3, -5, -6));
}

TEST(Matrix3x3Math, ScalarMultiplication) {
    // Arrange
    Matrix3x3f a(1, 2, 3,
                 4, 5, 6,
                 7, 8, 9);

    Matrix3x3f b(3, 4, 1,
                 5, 6, 0,
                 4, 2, 1);

    // Act
    Matrix3x3f result0 = a * 4;
    Matrix3x3f result1 = b * 7;

    // Assert
    ASSERT_TRUE(result0 == Matrix3x3f(4, 8, 12,
                                     16, 20, 24,
                                     28, 32, 36));

    ASSERT_TRUE(result1 == Matrix3x3f(21, 28, 7,
                                     35, 42, 0,
                                     28, 14, 7));
}

TEST(Matrix3x3Math, ScalarDivision) {
    // Arrange
    Matrix3x3f a(25, 0, 10,
                 15, 5, 30,
                 35, 100, 45);

    Matrix3x3f b(6, 4, 2,
                 0, 8, 16,
                 20, 10, 8);

    // Act
    Matrix3x3f result0 = a / 5;
    Matrix3x3f result1 = b / 2;

    // Assert
    ASSERT_TRUE(result0 == Matrix3x3f(5, 0, 2,
                                     3, 1, 6,
                                     7, 20, 9));

    ASSERT_TRUE(result1 == Matrix3x3f(3, 2, 1,
                                     0, 4, 8,
                                     10, 5, 4));
}

TEST(Matrix3x3Functions, Transpose) {
    // Arrange
    Matrix3x3f a(1, 2, 3,
                 4, 5, 6,
                 7, 8, 9);

    Matrix3x3f b(3, 4, 1,
                 5, 6, 0,
                 4, 2, 1);

    // Act
    Matrix3x3f result0 = a.transpose();
    Matrix3x3f result1 = b.transpose();

    // Assert
    ASSERT_TRUE(result0 == Matrix3x3f(1, 4, 7,
                                     2, 5, 8,
                                     3, 6, 9));

    ASSERT_TRUE(result1 == Matrix3x3f(3, 5, 4,
                                     4, 6, 2,
                                     1, 0, 1));
}

TEST(Matrix3x3Functions, Inverse) {
    // Arrange
    Matrix3x3f a(5, 6, 3,
                 4, 5, 6,
                 7, 8, 9);

    Matrix3x3f b(3, 4, 1,
                 5, 6, 0,
                 4, 2, 1);

    // Act
    Matrix3x3f result0 = a.inverse();
    Matrix3x3f result1 = b.inverse();

    // Assert
    ASSERT_FLOAT_EQ(result0(0, 0), -0.25f);
    ASSERT_FLOAT_EQ(result0(0, 1), -2.5f);
    ASSERT_FLOAT_EQ(result0(0, 2), 1.75f);
    ASSERT_FLOAT_EQ(result0(1, 0), 0.5f);
    ASSERT_FLOAT_EQ(result0(1, 1), 2.0f);
    ASSERT_FLOAT_EQ(result0(1, 2), -1.5f);
    ASSERT_FLOAT_EQ(result0(2, 0), -0.25f);
    ASSERT_FLOAT_EQ(result0(2, 1), 0.1666667f);
    ASSERT_FLOAT_EQ(result0(2, 2), 0.08333333f);

    ASSERT_FLOAT_EQ(result1(0, 0), -0.375f);
    ASSERT_FLOAT_EQ(result1(0, 1), 0.125f);
    ASSERT_FLOAT_EQ(result1(0, 2), 0.375f);
    ASSERT_FLOAT_EQ(result1(1, 0), 0.3125f);
    ASSERT_FLOAT_EQ(result1(1, 1), 0.0625f);
    ASSERT_FLOAT_EQ(result1(1, 2), -0.3125f);
    ASSERT_FLOAT_EQ(result1(2, 0), 0.875f);
    ASSERT_FLOAT_EQ(result1(2, 1), -0.625f);
    ASSERT_FLOAT_EQ(result1(2, 2), 0.125f);
}