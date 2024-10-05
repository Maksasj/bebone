#include "bebone/core/core.h"
#include "gtest/gtest.h"

using namespace bebone::core;

TEST(Matrix4x4Math, Initialization) {
    // Arrange
    Matrix4x4f a(4, 3, 1, 3,
                 2, 1, 0, 4,
                 5, 3, 2, 7,
                 1, 2, 3, 4);

    Matrix4x4f b(5, 6, 3, 3,
                 7, 8, 2, 4,
                 6, 3, 1, 3,
                 5, 3, 2, 1);
    // Act

    // Assert
    ASSERT_EQ(a(0, 0), 4);
    ASSERT_EQ(a(0, 1), 3);
    ASSERT_EQ(a(0, 2), 1);
    ASSERT_EQ(a(0, 3), 3);
    ASSERT_EQ(a(1, 0), 2);
    ASSERT_EQ(a(1, 1), 1);
    ASSERT_EQ(a(1, 2), 0);
    ASSERT_EQ(a(1, 3), 4);
    ASSERT_EQ(a(2, 0), 5);
    ASSERT_EQ(a(2, 1), 3);
    ASSERT_EQ(a(2, 2), 2);
    ASSERT_EQ(a(2, 3), 7);
    ASSERT_EQ(a(3, 0), 1);
    ASSERT_EQ(a(3, 1), 2);
    ASSERT_EQ(a(3, 2), 3);
    ASSERT_EQ(a(3, 3), 4);

    ASSERT_EQ(b(0, 0), 5);
    ASSERT_EQ(b(0, 1), 6);
    ASSERT_EQ(b(0, 2), 3);
    ASSERT_EQ(b(0, 3), 3);
    ASSERT_EQ(b(1, 0), 7);
    ASSERT_EQ(b(1, 1), 8);
    ASSERT_EQ(b(1, 2), 2);
    ASSERT_EQ(b(1, 3), 4);
    ASSERT_EQ(b(2, 0), 6);
    ASSERT_EQ(b(2, 1), 3);
    ASSERT_EQ(b(2, 2), 1);
    ASSERT_EQ(b(2, 3), 3);
    ASSERT_EQ(b(3, 0), 5);
    ASSERT_EQ(b(3, 1), 3);
    ASSERT_EQ(b(3, 2), 2);
    ASSERT_EQ(b(3, 3), 1);
}

TEST(Matrix4x4Math, MatrixAddition) {
    // Arrange
    Matrix4x4f a(1, 2, 3, 4,
                 5, 6, 7, 8,
                 9, 10, 11, 12,
                 13, 14, 15, 16);

    Matrix4x4f b(3, 4, 1, 4,
                 5, 6, 0, 3,
                 4, 2, 1, 2,
                 5, 1, 0, 3);

    Matrix4x4f c(3, 1, 4, 3,
                 5, 4, 3, 5,
                 6, 0, 0, 4,
                 2, 3, 5, 1);

    // Act
    Matrix4x4f result0 = a + b;
    Matrix4x4f result1 = b + c;

    // Assert
    ASSERT_TRUE(result0 == Matrix4x4f(4, 6, 4, 8,
                                     10, 12, 7, 11,
                                     13, 12, 12, 14,
                                     18, 15, 15, 19));

    ASSERT_TRUE(result1 == Matrix4x4f(6, 5, 5, 7,
                                     10, 10, 3, 8,
                                     10, 2, 1, 6,
                                     7, 4, 5, 4));
}

TEST(Matrix4x4Math, MatrixSubtraction) {
    // Arrange
    Matrix4x4f a(1, 2, 3, 4,
                 5, 6, 7, 8,
                 9, 10, 11, 12,
                 13, 14, 15, 16);

    Matrix4x4f b(3, 4, 1, 4,
                 5, 6, 0, 3,
                 4, 2, 1, 2,
                 5, 1, 0, 3);

    Matrix4x4f c(3, 1, 4, 3,
                 5, 4, 3, 5,
                 6, 0, 0, 4,
                 2, 3, 5, 1);

    // Act
    Matrix4x4f result0 = a - b;
    Matrix4x4f result1 = a - c;

    // Assert
    ASSERT_TRUE(result0 == Matrix4x4f(-2, -2, 2, 0,
                                     0, 0, 7, 5,
                                     5, 8, 10, 10,
                                     8, 13, 15, 13));

    ASSERT_TRUE(result1 == Matrix4x4f(-2, 1, -1, 1,
                                     0, 2, 4, 3,
                                     3, 10, 11, 8,
                                     11, 11, 10, 15));
}

TEST(Matrix4x4Math, MatrixMultiplication) {
    // Arrange
    Matrix4x4f a(1, 2, 3, 4,
                 5, 6, 7, 8,
                 9, 10, 11, 12,
                 13, 14, 15, 16);

    Matrix4x4f b(3, 4, 1, 4,
                 5, 6, 0, 3,
                 4, 2, 1, 2,
                 5, 1, 0, 3);

    Matrix4x4f c(3, 1, 4, 3,
                 5, 4, 3, 5,
                 6, 0, 0, 4,
                 2, 3, 5, 1);

    // Act
    Matrix4x4f result0 = a * b;
    Matrix4x4f result1 = b * a;
    Matrix4x4f result2 = b * c;
    Matrix4x4f result3 = c * b;

    // Assert
    ASSERT_TRUE(result0 == Matrix4x4f(45, 26, 4, 28,
                                     113, 78, 12, 76,
                                     181, 130, 20, 124,
                                     249, 182, 28, 172));

    ASSERT_TRUE(result1 == Matrix4x4f(84, 96, 108, 120,
                                     74, 88, 102, 116,
                                     49, 58, 67, 76,
                                     49, 58, 67, 76));

    ASSERT_TRUE(result2 == Matrix4x4f(43, 31, 44, 37,
                                     51, 38, 53, 48,
                                     32, 18, 32, 28,
                                     26, 18, 38, 23));

    ASSERT_TRUE(result3 == Matrix4x4f(45, 29, 7, 32,
                                     72, 55, 8, 53,
                                     38, 28, 6, 36,
                                     46, 37, 7, 30));
}

TEST(Matrix4x4Math, ScalarAddition) {
    // Arrange
    Matrix4x4f a(1, 2, 3, 4,
                 5, 6, 7, 8,
                 9, 10, 11, 12,
                 13, 14, 15, 16);

    Matrix4x4f b(3, 4, 1, 4,
                 5, 6, 0, 3,
                 4, 2, 1, 2,
                 5, 1, 0, 3);

    // Act
    Matrix4x4f result0 = a + 4;
    Matrix4x4f result1 = b + 7;

    // Assert
    ASSERT_TRUE(result0 == Matrix4x4f(5, 6, 7, 8,
                                     9, 10, 11, 12,
                                     13, 14, 15, 16,
                                     17, 18, 19, 20));

    ASSERT_TRUE(result1 == Matrix4x4f(10, 11, 8, 11,
                                     12, 13, 7, 10,
                                     11, 9, 8, 9,
                                     12, 8, 7, 10));
}

TEST(Matrix4x4Math, ScalarSubtraction) {
    // Arrange
    Matrix4x4f a(1, 2, 3, 4,
                 5, 6, 7, 8,
                 9, 10, 11, 12,
                 13, 14, 15, 16);

    Matrix4x4f b(3, 4, 1, 4,
                 5, 6, 0, 3,
                 4, 2, 1, 2,
                 5, 1, 0, 3);

    // Act
    Matrix4x4f result0 = a - 4;
    Matrix4x4f result1 = b - 7;

    // Assert
    ASSERT_TRUE(result0 == Matrix4x4f(-3, -2, -1, 0,
                                     1, 2, 3, 4,
                                     5, 6, 7, 8,
                                     9, 10, 11, 12));

    ASSERT_TRUE(result1 == Matrix4x4f(-4, -3, -6, -3,
                                     -2, -1, -7, -4,
                                     -3, -5, -6, -5,
                                     -2, -6, -7, -4));
}

TEST(Matrix4x4Math, ScalarMultiplication) {
    // Arrange
    Matrix4x4f a(1, 2, 3, 4,
                 5, 6, 7, 8,
                 9, 10, 11, 12,
                 13, 14, 15, 16);

    Matrix4x4f b(3, 4, 1, 4,
                 5, 6, 0, 3,
                 4, 2, 1, 2,
                 5, 1, 0, 3);

    // Act
    Matrix4x4f result0 = a * 4;
    Matrix4x4f result1 = b * 7;

    // Assert
    ASSERT_TRUE(result0 == Matrix4x4f(4, 8, 12, 16,
                                     20, 24, 28, 32,
                                     36, 40, 44, 48,
                                     52, 56, 60, 64));

    ASSERT_TRUE(result1 == Matrix4x4f(21, 28, 7, 28,
                                     35, 42, 0, 21,
                                     28, 14, 7, 14,
                                     35, 7, 0, 21));
}

TEST(Matrix4x4Math, ScalarDivision) {
    // Arrange
    Matrix4x4f a(25, 0, 10, 15,
                 15, 5, 30, 30,
                 35, 100, 45, 60,
                 0, 5, 5, 10);

    Matrix4x4f b(6, 4, 2, 8,
                 0, 8, 16, 12,
                 20, 10, 8, 16,
                 0, 8, 6, 2);

    // Act
    Matrix4x4f result0 = a / 5;
    Matrix4x4f result1 = b / 2;

    // Assert
    ASSERT_TRUE(result0 == Matrix4x4f(5, 0, 2, 3,
                                     3, 1, 6, 6,
                                     7, 20, 9, 12,
                                     0, 1, 1, 2));

    ASSERT_TRUE(result1 == Matrix4x4f(3, 2, 1, 4,
                                     0, 4, 8, 6,
                                     10, 5, 4, 8,
                                     0, 4, 3, 1));
}

TEST(Matrix4x4functions, Transpose) {
    // Arrange
    Matrix4x4f a(1, 2, 3, 4,
                 5, 6, 7, 8,
                 9, 10, 11, 12,
                 13, 14, 15, 16);

    Matrix4x4f b(3, 4, 1, 4,
                 5, 6, 0, 3,
                 4, 2, 1, 2,
                 5, 1, 0, 3);

    // Act
    Matrix4x4f result0 = a.transpose();
    Matrix4x4f result1 = b.transpose();

    // Assert
    ASSERT_TRUE(result0 == Matrix4x4f(1, 5, 9, 13,
                                     2, 6, 10, 14,
                                     3, 7, 11, 15,
                                     4, 8, 12, 16));

    ASSERT_TRUE(result1 == Matrix4x4f(3, 5, 4, 5,
                                     4, 6, 2, 1,
                                     1, 0, 1, 0,
                                     4, 3, 2, 3));
}

TEST(Matrix4x4functions, Inverse) {
    // Arrange
    Matrix4x4f a(7, 8, 5, 0,
                 7, 5, 3, 5,
                 9, 0, 8, 8,
                 5, 1, 15, 8);

    Matrix4x4f b(3, 4, 1, 4,
                 5, 6, 0, 3,
                 4, 2, 1, 2,
                 5, 1, 0, 3);

    // Act
    Matrix4x4f result0 = a.inverse();
    Matrix4x4f result1 = b.inverse();

    // Assert
    ASSERT_FLOAT_EQ(result0(0, 0), 0.10485299f);
    ASSERT_FLOAT_EQ(result0(0, 1), -0.14452709f);
    ASSERT_FLOAT_EQ(result0(0, 2), 0.20651788f);
    ASSERT_FLOAT_EQ(result0(0, 3), -0.11618845f);
    ASSERT_FLOAT_EQ(result0(1, 0), -0.00460503f);
    ASSERT_FLOAT_EQ(result0(1, 1), 0.19553666f);
    ASSERT_FLOAT_EQ(result0(1, 2), -0.18136733f);
    ASSERT_FLOAT_EQ(result0(1, 3), 0.05915692f);
    ASSERT_FLOAT_EQ(result0(2, 0), 0.06057385f);
    ASSERT_FLOAT_EQ(result0(2, 1), -0.11052072f);
    ASSERT_FLOAT_EQ(result0(2, 2), 0.0010626987f);
    ASSERT_FLOAT_EQ(result0(2, 3), 0.06801275f);
    ASSERT_FLOAT_EQ(result0(3, 0), -0.17853347f);
    ASSERT_FLOAT_EQ(result0(3, 1), 0.27311370f);
    ASSERT_FLOAT_EQ(result0(3, 2), -0.10839532f);
    ASSERT_FLOAT_EQ(result0(3, 3), 0.06269925f);

    ASSERT_FLOAT_EQ(result1(0, 0), -0.23076923f);
    ASSERT_FLOAT_EQ(result1(0, 1), 0.06153846f);
    ASSERT_FLOAT_EQ(result1(0, 2), 0.23076923f);
    ASSERT_FLOAT_EQ(result1(0, 3), 0.09230769f);
    ASSERT_FLOAT_EQ(result1(1, 0), 0.0f);
    ASSERT_FLOAT_EQ(result1(1, 1), 0.2f);
    ASSERT_FLOAT_EQ(result1(1, 2), 0.0f);
    ASSERT_FLOAT_EQ(result1(1, 3), -0.2f);
    ASSERT_FLOAT_EQ(result1(2, 0), 0.15384615f);
    ASSERT_FLOAT_EQ(result1(2, 1), -0.30769230f);
    ASSERT_FLOAT_EQ(result1(2, 2), 0.84615384f);
    ASSERT_FLOAT_EQ(result1(2, 3), -0.46153846f);
    ASSERT_FLOAT_EQ(result1(3, 0), 0.38461538f);
    ASSERT_FLOAT_EQ(result1(3, 1), -0.16923076f);
    ASSERT_FLOAT_EQ(result1(3, 2), -0.38461538f);
    ASSERT_FLOAT_EQ(result1(3, 3), 0.24615384f);
}