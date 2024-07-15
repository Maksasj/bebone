#include "bebone/core/core.h"
#include "gtest/gtest.h"

using namespace bebone::core;

TEST(Vector3Math, Addition) {
    Vec3f a(2.4f, 2.0f, 1.0f);
    Vec3f b(3.4f, 45.0, 4.0f);
    Vec3f result(5.8f, 47.0f, 5.0f);

    ASSERT_EQ(a + b, result);
    ASSERT_EQ(b + a, result);
    ASSERT_EQ(a, Vec3f(2.4f, 2.0f, 1.0f));
    ASSERT_EQ(b, Vec3f(3.4f, 45.0f, 4.0f));

    a += b;
    ASSERT_EQ(a, result);
    ASSERT_EQ(b, Vec3f(3.4f, 45.0f, 4.0f));
}

TEST(Vector3Math, Subtraction) {
    Vec3f a(4.4f, 47.0f, 2.0f);
    Vec3f b(3.4f, 45.0, 3.0f);
    Vec3f result(1.0f, 2.0f, -1.0f);

    ASSERT_EQ(a - b, result);
    ASSERT_EQ(b - a, -result);
    ASSERT_EQ(a, Vec3f(4.4f, 47.0f, 2.0f));
    ASSERT_EQ(b, Vec3f(3.4f, 45.0, 3.0f));

    a -= b;
    ASSERT_EQ(a, result);
    ASSERT_EQ(b, Vec3f(3.4f, 45.0f, 3.0f));
}

TEST(Vector3Math, Multiplication) {
    Vec3f a(5.0f, 1.0f, 3.0f);
    Vec3f b(2.1f, 7.0f, 2.0f);
    Vec3f result(10.5f, 7.0f, 6.0f);

    ASSERT_EQ(a * b, result);
    ASSERT_EQ(b * a, result);
    ASSERT_EQ(a, Vec3f(5.0f, 1.0f, 3.0f));
    ASSERT_EQ(b, Vec3f(2.1f, 7.0f, 2.0f));

    a *= b;
    ASSERT_EQ(a, result);
    ASSERT_EQ(b, Vec3f(2.1f, 7.0f, 2.0f));
}

TEST(Vector3Math, Division) {
    Vec3f a(7.0f, 8.0f, 3.5f);
    Vec3f b(2.0f, 4.0f, 0.5f);
    Vec3f result(3.5f, 2.0f, 7.0f);

    ASSERT_EQ(a / b, result);

    ASSERT_FLOAT_EQ((b / a).x, 0.2857142f);
    ASSERT_EQ((b / a).y, 0.5f);
    ASSERT_FLOAT_EQ((b / a).z, 0.1428571f);

    ASSERT_EQ(a, Vec3f(7.0f, 8.0f, 3.5f));
    ASSERT_EQ(b, Vec3f(2.0f, 4.0f, 0.5f));

    a /= b;
    ASSERT_EQ(a, result);
    ASSERT_EQ(b, Vec3f(2.0f, 4.0f, 0.5f));
}

TEST(Vector3Math, Negation) {
    Vec3f a(7.0f, -8.0f, 4.3f);
    Vec3f b(-2.0f, 0.0f, 5.4f);

    ASSERT_EQ(-a, Vec3f(-7.0f, 8.0f, -4.3f));
    ASSERT_EQ(-b, Vec3f(2.0f, 0.0f, -5.4f));
}

TEST(Vector3Functions, Absolute) {
    Vec3f a(-5.0f, -3.0f, -2.0f);
    Vec3f b(-1.0f, 2.0f, -3.0f);
    Vec3f c = Vec3f::zero;

    ASSERT_EQ(a.abs(), Vec3f(5.0f, 3.0f, 2.0f));
    ASSERT_EQ(b.abs(), Vec3f(1.0f, 2.0f, 3.0f));
    ASSERT_EQ(c.abs(), Vec3f::zero);
}

TEST(Vector3Functions, Length) {
    Vec3f a(3.0f, 4.0f, 12.0f);
    Vec3f b(3.8f, 2.3f, 4.5f);
    Vec3f c(23.5f, 12.4f, 15.3f);

    ASSERT_EQ(a.length(), 13);
    ASSERT_FLOAT_EQ(b.length(), 6.3229739f);
    ASSERT_FLOAT_EQ(c.length(), 30.6610502f);
}

TEST(Vector3Functions, Normalization) {
    Vec3f a(2.5f, 1.2f, -3.0f);
    Vec3f b(-1.4f, 3.7f, 2.4f);
    Vec3f c = Vec3f::right;
    Vec3f d = Vec3f::up;
    Vec3f e = Vec3f::left;
    Vec3f f = Vec3f::down;

    Vec3f a_normalized = a.normalize();
    Vec3f b_normalized = b.normalize();

    ASSERT_FLOAT_EQ(a_normalized.x, 0.6119442f);
    ASSERT_FLOAT_EQ(a_normalized.y, 0.2937332f);
    ASSERT_FLOAT_EQ(a_normalized.z, -0.7343330f);

    ASSERT_FLOAT_EQ(b_normalized.x, -0.3025657f);
    ASSERT_FLOAT_EQ(b_normalized.y, 0.7996379f);
    ASSERT_FLOAT_EQ(b_normalized.z, 0.5186840f);

    ASSERT_EQ(c.normalize(), Vec3f::right);
    ASSERT_EQ(d.normalize(), Vec3f::up);
    ASSERT_EQ(e.normalize(), Vec3f::left);
    ASSERT_EQ(f.normalize(), Vec3f::down);
}

TEST(Vector3Functions, Splat) {
    ASSERT_EQ(Vec3f::splat(1.0f), Vec3f(1.0f, 1.0f, 1.0f));
    ASSERT_EQ(Vec3f::splat(5.0f), Vec3f(5.0f, 5.0f, 5.0f));
}

TEST(Vector3Functions, Dot) {
    Vec3f a(1.3f, 4.5f, 3.4f);
    Vec3f b(2.5f, 3.7f, 1.4f);
    Vec3f c(6.7f, 1.3f, 2.5f);

    ASSERT_FLOAT_EQ(Vec3f::dot(a, b), 24.66f);
    ASSERT_FLOAT_EQ(Vec3f::dot(b, a), 24.66f);
    ASSERT_FLOAT_EQ(Vec3f::dot(b, c), 25.06f);
    ASSERT_FLOAT_EQ(Vec3f::dot(c, b), 25.06f);
}

TEST(Vector3Functions, Cross) {
    Vec3f a(1.3f, 4.5f, 3.4f);
    Vec3f b(2.5f, 3.7f, 1.4f);
    Vec3f c(6.7f, 1.3f, 2.5f);

    ASSERT_FLOAT_EQ(Vec3f::cross(a, b).x, -6.28f);
    ASSERT_FLOAT_EQ(Vec3f::cross(a, b).y, 6.68f);
    ASSERT_FLOAT_EQ(Vec3f::cross(a, b).z, -6.44f);

    ASSERT_FLOAT_EQ(Vec3f::cross(b, a).x, 6.28f);
    ASSERT_FLOAT_EQ(Vec3f::cross(b, a).y, -6.68f);
    ASSERT_FLOAT_EQ(Vec3f::cross(b, a).z, 6.44f);

    ASSERT_FLOAT_EQ(Vec3f::cross(b, c).x, 7.43f);
    ASSERT_FLOAT_EQ(Vec3f::cross(b, c).y, 3.13f);
    ASSERT_FLOAT_EQ(Vec3f::cross(b, c).z, -21.54f);

    ASSERT_FLOAT_EQ(Vec3f::cross(c, b).x, -7.43f);
    ASSERT_FLOAT_EQ(Vec3f::cross(c, b).y, -3.13f);
    ASSERT_FLOAT_EQ(Vec3f::cross(c, b).z, 21.54f);
}

TEST(Vector3Functions, Projection) {
    Vec3f a(4.0f, 5.0f, 6.0f);
    Vec3f b(3.0f, -3.0f, 3.0f);
    Vec3f c(2.5f, -6.4f, 4.5f);

    ASSERT_FLOAT_EQ(Vec3f::project(a, b).x, 1.666667f);
    ASSERT_FLOAT_EQ(Vec3f::project(a, b).y, -1.666667f);
    ASSERT_FLOAT_EQ(Vec3f::project(a, b).z, 1.666667f);

    ASSERT_FLOAT_EQ(Vec3f::project(b, a).x, 0.7792207f);
    ASSERT_FLOAT_EQ(Vec3f::project(b, a).y, 0.9740259f);
    ASSERT_FLOAT_EQ(Vec3f::project(b, a).z, 1.1688311f);

    ASSERT_FLOAT_EQ(Vec3f::project(b, c).x, 1.4897717f);
    ASSERT_FLOAT_EQ(Vec3f::project(b, c).y, -3.8138155f);
    ASSERT_FLOAT_EQ(Vec3f::project(b, c).z, 2.6815890f);

    ASSERT_FLOAT_EQ(Vec3f::project(c, b).x, 4.4666667f);
    ASSERT_FLOAT_EQ(Vec3f::project(c, b).y, -4.4666667f);
    ASSERT_FLOAT_EQ(Vec3f::project(c, b).z, 4.4666667f);
}

TEST(Vector3Functions, Rejection) {
    Vec3f a(4.0f, 5.0f, 6.0f);
    Vec3f b(3.0f, -3.0f, 3.0f);
    Vec3f c(2.5f, -6.4f, 4.5f);

    ASSERT_FLOAT_EQ(Vec3f::reject(a, b).x, 2.333333f);
    ASSERT_FLOAT_EQ(Vec3f::reject(a, b).y, 6.666667f);
    ASSERT_FLOAT_EQ(Vec3f::reject(a, b).z, 4.333333f);

    ASSERT_FLOAT_EQ(Vec3f::reject(b, a).x, 2.2207793f);
    ASSERT_FLOAT_EQ(Vec3f::reject(b, a).y, -3.9740259f);
    ASSERT_FLOAT_EQ(Vec3f::reject(b, a).z, 1.8311689f);

    ASSERT_FLOAT_EQ(Vec3f::reject(b, c).x, 1.5102283f);
    ASSERT_FLOAT_EQ(Vec3f::reject(b, c).y, 0.8138155f);
    ASSERT_FLOAT_EQ(Vec3f::reject(b, c).z, 0.318411f);

    ASSERT_FLOAT_EQ(Vec3f::reject(c, b).x, -1.9666667f);
    ASSERT_FLOAT_EQ(Vec3f::reject(c, b).y, -1.9333333f);
    ASSERT_FLOAT_EQ(Vec3f::reject(c, b).z, 0.0333333f);
}