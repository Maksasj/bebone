#include "bebone/core/core.h"
#include "gtest/gtest.h"

using namespace bebone::core;

TEST(Matrix2x2Math, Initialization) {
    // Arrange
    Matrix2x2f a(4, 3,
                 2, 1);

    Matrix2x2f b(5, 6,
                 7, 8);

    // Act

    // Assert
    ASSERT_EQ(a(0, 0), 4);
    ASSERT_EQ(a(0, 1), 3);
    ASSERT_EQ(a(1, 0), 2);
    ASSERT_EQ(a(1, 1), 1);

    ASSERT_EQ(b(0, 0), 5);
    ASSERT_EQ(b(0, 1), 6);
    ASSERT_EQ(b(1, 0), 7);
    ASSERT_EQ(b(1, 1), 8);
}

TEST(Matrix2x2Math, MatrixAddition) {
    // Arrange
    Matrix2x2f a(1, 2,
                 3, 4);

    Matrix2x2f b(3, 4,
                 5, 6);

    Matrix2x2f c(3, 1,
                 5, 4);
    // Act
    Matrix2x2f result0 = a + b;
    Matrix2x2f result1 = b + c;

    // Assert
    ASSERT_TRUE(result0 == Matrix2x2f(4, 6,
                                     8, 10));

    ASSERT_TRUE(result1 == Matrix2x2f(6, 5,
                                     10, 10));
}

TEST(Matrix2x2Math, MatrixSubtraction) {
    // Arrange
    Matrix2x2f a(15, 7,
                 3, 8);

    Matrix2x2f b(0, 1,
                 4, 3);

    Matrix2x2f c(6, 4,
                 3, 5);

    // Act
    Matrix2x2f result0 = a - b;
    Matrix2x2f result1 = a - c;

    // Assert
    ASSERT_TRUE(result0 == Matrix2x2f(15, 6,
                                     -1, 5));

    ASSERT_TRUE(result1 == Matrix2x2f(9, 3,
                                     0, 3));
}

TEST(Matrix2x2Math, MatrixMultiplication) {
    // Arrange
    Matrix2x2f a(15, 7,
                 3, 8);

    Matrix2x2f b(0, 1,
                 4, 3);

    Matrix2x2f c(6, 4,
                 3, 5);

    // Act
    Matrix2x2f result0 = a * b;
    Matrix2x2f result1 = b * a;
    Matrix2x2f result2 = b * c;
    Matrix2x2f result3 = c * b;

    // Assert
    ASSERT_TRUE(result0 == Matrix2x2f(28, 36,
                                     32, 27));
    ASSERT_TRUE(result1 == Matrix2x2f(3, 8,
                                     69, 52));
    ASSERT_TRUE(result2 == Matrix2x2f(3, 5,
                                     33, 31));
    ASSERT_TRUE(result3 == Matrix2x2f(16, 18,
                                     20, 18));
}

TEST(Matrix2x2Math, ScalarAddition) {
    // Arrange
    Matrix2x2f a(5, 3,
                 2, 5);

    Matrix2x2f b(6, 2,
                 4, 0);

    // Act
    Matrix2x2f result0 = a + 4;
    Matrix2x2f result1 = b + 7;

    // Assert
    ASSERT_TRUE(result0 == Matrix2x2f(9, 7,
                                     6, 9));

    ASSERT_TRUE(result1 == Matrix2x2f(13, 9,
                                     11, 7));
}

TEST(Matrix2x2Math, ScalarSubtraction) {
    // Arrange
    Matrix2x2f a(5, 3,
                 2, 5);

    Matrix2x2f b(6, 2,
                 4, 0);

    // Act
    Matrix2x2f result0 = a - 4;
    Matrix2x2f result1 = b - 7;

    // Assert
    ASSERT_TRUE(result0 == Matrix2x2f(1, -1,
                                     -2, 1));

    ASSERT_TRUE(result1 == Matrix2x2f(-1, -5,
                                     -3, -7));
}

TEST(Matrix2x2Math, ScalarMultiplication) {
    // Arrange
    Matrix2x2f a(5, 3,
                 2, 5);

    Matrix2x2f b(6, 2,
                 4, 0);

    // Act
    Matrix2x2f result0 = a * 4;
    Matrix2x2f result1 = b * 7;

    // Assert
    ASSERT_TRUE(result0 == Matrix2x2f(20, 12,
                                     8, 20));

    ASSERT_TRUE(result1 == Matrix2x2f(42, 14,
                                     28, 0));
}

TEST(Matrix2x2Math, ScalarDivision) {
    // Arrange
    Matrix2x2f a(5, 25,
                 10, 5);

    Matrix2x2f b(6, 2,
                 4, 0);

    // Act
    Matrix2x2f result0 = a / 5;
    Matrix2x2f result1 = b / 2;

    // Assert
    ASSERT_TRUE(result0 == Matrix2x2f(1, 5,
                                     2, 1));

    ASSERT_TRUE(result1 == Matrix2x2f(3, 1,
                                     2, 0));
}

TEST(Matrix2x2Functions, Transpose) {
    // Arrange
    Matrix2x2f a(1, 2,
                 3, 4);

    Matrix2x2f b(47, 4,
                 8, 0);

    // Act
    Matrix2x2f result0 = a.transpose();
    Matrix2x2f result1 = b.transpose();

    // Assert
    ASSERT_TRUE(result0 == Matrix2x2f(1, 3,
                                     2, 4));

    ASSERT_TRUE(result1 == Matrix2x2f(47, 8,
                                     4, 0));
}

TEST(Matrix2x2Functions, Inverse) {
    // Arrange
    Matrix2x2f a(5, 2,
                 4, 10);

    Matrix2x2f b(4, 4,
                 0, 2);

    // Act
    Matrix2x2f result0 = a.inverse();
    Matrix2x2f result1 = b.inverse();

    // Assert
    ASSERT_FLOAT_EQ(result0(0, 0), 0.2380952f);
    ASSERT_FLOAT_EQ(result0(0, 1), -0.047619049f);
    ASSERT_FLOAT_EQ(result0(1, 0), -0.095238097f);
    ASSERT_FLOAT_EQ(result0(1, 1), 0.1190476f);

    ASSERT_FLOAT_EQ(result1(0, 0), 0.25f);
    ASSERT_FLOAT_EQ(result1(0, 1), -0.5f);
    ASSERT_FLOAT_EQ(result1(1, 0), 0);
    ASSERT_FLOAT_EQ(result1(1, 1), 0.5f);
}