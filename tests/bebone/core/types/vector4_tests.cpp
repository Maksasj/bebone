#include "bebone/core/core.h"
#include "gtest/gtest.h"

using namespace bebone::core;

TEST(Vector4Math, Addition) {
    Vec4f a(2.4f, 2.0f, 1.0f, 0.0f);
    Vec4f b(3.4f, 45.0, 4.0f, 4.0f);
    Vec4f result(5.8f, 47.0f, 5.0f, 4.0f);

    ASSERT_EQ(a + b, result);
    ASSERT_EQ(b + a, result);
    ASSERT_EQ(a, Vec4f(2.4f, 2.0f, 1.0f, 0.0f));
    ASSERT_EQ(b, Vec4f(3.4f, 45.0f, 4.0f, 4.0f));

    a += b;
    ASSERT_EQ(a, result);
    ASSERT_EQ(b, Vec4f(3.4f, 45.0f, 4.0f, 4.0f));
}

TEST(Vector4Math, Subtraction) {
    Vec4f a(4.4f, 47.0f, 2.0f, 5.0f);
    Vec4f b(3.4f, 45.0, 3.0f, 2.0f);
    Vec4f result(1.0f, 2.0f, -1.0f, 3.0f);

    ASSERT_EQ(a - b, result);
    ASSERT_EQ(b - a, -result);
    ASSERT_EQ(a, Vec4f(4.4f, 47.0f, 2.0f, 5.0f));
    ASSERT_EQ(b, Vec4f(3.4f, 45.0, 3.0f, 2.0f));

    a -= b;
    ASSERT_EQ(a, result);
    ASSERT_EQ(b, Vec4f(3.4f, 45.0f, 3.0f, 2.0f));
}

TEST(Vector4Math, Multiplication) {
    Vec4f a(5.0f, 1.0f, 3.0f, 2.0f);
    Vec4f b(2.1f, 7.0f, 2.0f, 1.0f);
    Vec4f result(10.5f, 7.0f, 6.0f, 2.0f);

    ASSERT_EQ(a * b, result);
    ASSERT_EQ(b * a, result);
    ASSERT_EQ(a, Vec4f(5.0f, 1.0f, 3.0f, 2.0f));
    ASSERT_EQ(b, Vec4f(2.1f, 7.0f, 2.0f, 1.0f));

    a *= b;
    ASSERT_EQ(a, result);
    ASSERT_EQ(b, Vec4f(2.1f, 7.0f, 2.0f, 1.0f));
}

TEST(Vector4Math, Division) {
    Vec4f a(7.0f, 8.0f, 3.5f, 5.0f);
    Vec4f b(2.0f, 4.0f, 0.5f, 5.0f);
    Vec4f result(3.5f, 2.0f, 7.0f, 1.0f);

    ASSERT_EQ(a / b, result);

    ASSERT_FLOAT_EQ((b / a).x, 0.2857142f);
    ASSERT_EQ((b / a).y, 0.5f);
    ASSERT_FLOAT_EQ((b / a).z, 0.1428571f);
    ASSERT_EQ((b / a).w, 1.0f);

    ASSERT_EQ(a, Vec4f(7.0f, 8.0f, 3.5f, 5.0f));
    ASSERT_EQ(b, Vec4f(2.0f, 4.0f, 0.5f, 5.0f));

    a /= b;
    ASSERT_EQ(a, result);
    ASSERT_EQ(b, Vec4f(2.0f, 4.0f, 0.5f, 5.0f));
}

TEST(Vector4Math, Negation) {
    Vec4f a(7.0f, -8.0f, 4.3f, 3.0f);
    Vec4f b(-2.0f, 0.0f, 5.4f, 2.5f);

    ASSERT_EQ(-a, Vec4f(-7.0f, 8.0f, -4.3f, -3.0f));
    ASSERT_EQ(-b, Vec4f(2.0f, 0.0f, -5.4f, -2.5f));
}

TEST(Vector4Functions, Absolute) {
    Vec4f a(-5.0f, -3.0f, -2.0f, 3.0f);
    Vec4f b(-1.0f, 2.0f, -3.0f, -3.0f);
    Vec4f c = Vec4f::zero;

    ASSERT_EQ(a.abs(), Vec4f(5.0f, 3.0f, 2.0f, 3.0f));
    ASSERT_EQ(b.abs(), Vec4f(1.0f, 2.0f, 3.0f, -3.0f));
    ASSERT_EQ(c.abs(), Vec4f::zero);
}

TEST(Vector4Functions, Length) {
    Vec4f a(3.0f, 4.0f, 12.0f, 6.0f);
    Vec4f b(3.8f, 2.3f, 4.5f, 6.0f);
    Vec4f c(23.5f, 12.4f, 15.3f, 1.0f);

    ASSERT_FLOAT_EQ(a.length(), 14.3178210f);
    ASSERT_FLOAT_EQ(b.length(), 8.7166507f);
    ASSERT_FLOAT_EQ(c.length(), 30.6773532f);
}

TEST(Vector4Functions, Normalization) {
    Vec4f a(2.5f, 1.2f, -3.0f, 1.0f);
    Vec4f b(-1.4f, 3.7f, 2.4f, 0.0f);

    Vec4f a_normalized = a.normalize();
    Vec4f b_normalized = b.normalize();

    ASSERT_FLOAT_EQ(a_normalized.x, 0.5943962f);
    ASSERT_FLOAT_EQ(a_normalized.y, 0.2853102f);
    ASSERT_FLOAT_EQ(a_normalized.z, -0.7132755f);
    ASSERT_FLOAT_EQ(a_normalized.w, 0.2377585f);

    ASSERT_FLOAT_EQ(b_normalized.x, -0.3025657f);
    ASSERT_FLOAT_EQ(b_normalized.y, 0.7996379f);
    ASSERT_FLOAT_EQ(b_normalized.z, 0.5186840f);
    ASSERT_FLOAT_EQ(b_normalized.w, 0.0f);
}

TEST(Vector4Functions, Splat) {
    ASSERT_EQ(Vec4f::splat(1.0f), Vec4f(1.0f, 1.0f, 1.0f, 1.0f));
    ASSERT_EQ(Vec4f::splat(5.0f), Vec4f(5.0f, 5.0f, 5.0f, 5.0f));
}

TEST(Vector4Functions, Dot) {
    Vec4f a(1.3f, 4.5f, 3.4f, 2.0f);
    Vec4f b(2.5f, 3.7f, 1.4f, 1.0f);
    Vec4f c(6.7f, 1.3f, 2.5f, 0.0f);

    ASSERT_FLOAT_EQ(Vec4f::dot(a, b), 26.66f);
    ASSERT_FLOAT_EQ(Vec4f::dot(b, a), 26.66f);
    ASSERT_FLOAT_EQ(Vec4f::dot(b, c), 25.06f);
    ASSERT_FLOAT_EQ(Vec4f::dot(c, b), 25.06f);
}

TEST(Vector4Functions, Projection) {
    Vec4f a(4.0f, 5.0f, 6.0f, 7.0f);
    Vec4f b(3.0f, -3.0f, 3.0f, -3.0f);
    Vec4f c(2.5f, -6.4f, 4.5f, 1.0f);

    ASSERT_FLOAT_EQ(Vec4f::project(a, b).x, -0.5f);
    ASSERT_FLOAT_EQ(Vec4f::project(a, b).y, 0.5f);
    ASSERT_FLOAT_EQ(Vec4f::project(a, b).z, -0.5f);
    ASSERT_FLOAT_EQ(Vec4f::project(a, b).w, 0.5f);

    ASSERT_FLOAT_EQ(Vec4f::project(b, a).x, -0.19047619f);
    ASSERT_FLOAT_EQ(Vec4f::project(b, a).y, -0.2380952f);
    ASSERT_FLOAT_EQ(Vec4f::project(b, a).z, -0.2857142f);
    ASSERT_FLOAT_EQ(Vec4f::project(b, a).w, -0.3333333f);

    ASSERT_FLOAT_EQ(Vec4f::project(b, c).x, 1.3584574f);
    ASSERT_FLOAT_EQ(Vec4f::project(b, c).y, -3.4776511f);
    ASSERT_FLOAT_EQ(Vec4f::project(b, c).z, 2.4452234f);
    ASSERT_FLOAT_EQ(Vec4f::project(b, c).w, 0.5433829f);

    ASSERT_FLOAT_EQ(Vec4f::project(c, b).x, 3.1f);
    ASSERT_FLOAT_EQ(Vec4f::project(c, b).y, -3.1f);
    ASSERT_FLOAT_EQ(Vec4f::project(c, b).z, 3.1f);
    ASSERT_FLOAT_EQ(Vec4f::project(c, b).w, -3.1f);
}

TEST(Vector4Functions, Rejection) {
    Vec4f a(4.0f, 5.0f, 6.0f, 7.0f);
    Vec4f b(3.0f, -3.0f, 3.0f, -3.0f);
    Vec4f c(2.5f, -6.4f, 4.5f, 1.0f);

    ASSERT_FLOAT_EQ(Vec4f::reject(a, b).x, 4.5f);
    ASSERT_FLOAT_EQ(Vec4f::reject(a, b).y, 4.5f);
    ASSERT_FLOAT_EQ(Vec4f::reject(a, b).z, 6.5f);
    ASSERT_FLOAT_EQ(Vec4f::reject(a, b).w, 6.5f);

    ASSERT_FLOAT_EQ(Vec4f::reject(b, a).x, 3.1904761f);
    ASSERT_FLOAT_EQ(Vec4f::reject(b, a).y, -2.7619048f);
    ASSERT_FLOAT_EQ(Vec4f::reject(b, a).z, 3.2857142f);
    ASSERT_FLOAT_EQ(Vec4f::reject(b, a).w, -2.6666667f);

    ASSERT_FLOAT_EQ(Vec4f::reject(b, c).x, 1.6415427f);
    ASSERT_FLOAT_EQ(Vec4f::reject(b, c).y, 0.47765088f);
    ASSERT_FLOAT_EQ(Vec4f::reject(b, c).z, 0.55477667f);
    ASSERT_FLOAT_EQ(Vec4f::reject(b, c).w, -3.5433829f);

    ASSERT_FLOAT_EQ(Vec4f::reject(c, b).x, -0.6f);
    ASSERT_FLOAT_EQ(Vec4f::reject(c, b).y, -3.3f);
    ASSERT_FLOAT_EQ(Vec4f::reject(c, b).z, 1.4f);
    ASSERT_FLOAT_EQ(Vec4f::reject(c, b).w, 4.1f);
}

TEST(Vector4Functions, IsNormalized) {
    Vec4f b(5, 10, 4, 2);
    ASSERT_FALSE(b.is_normalized());

    Vec4f b_normalized = b.normalize();
    ASSERT_TRUE(b_normalized.is_normalized());
}

TEST(Vector4Conversions, ConversionToVec2) {
    Vec4f a(4.0f, 5.0f, 6.0f, 4.0f);
    Vec4f b(2.0f, 3.0f, 1.0f, 4.0f);

    ASSERT_EQ(Vec2f(a), Vec2f(4.0f, 5.0f));
    ASSERT_EQ(Vec2f(b), Vec2f(2.0f, 3.0f));
}

TEST(Vector4Conversions, ConversionToVec3) {
    Vec4f a(4.0f, 5.0f, 6.0f, 4.0f);
    Vec4f b(2.0f, 3.0f, 1.0f, 4.0f);

    ASSERT_EQ(Vec3f(a), Vec3f(4.0f, 5.0f, 6.0f));
    ASSERT_EQ(Vec3f(b), Vec3f(2.0f, 3.0f, 1.0f));
}