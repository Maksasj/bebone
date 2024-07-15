#include "bebone/core/core.h"
#include "gtest/gtest.h"

using namespace bebone::core;

TEST(Vector2Math, Addition) {
    Vec2f a(2.4f, 2.0f);
    Vec2f b(3.4f, 45.0);
    Vec2f result(5.8f, 47.0f);

    ASSERT_EQ(a + b, result);
    ASSERT_EQ(b + a, result);
    ASSERT_EQ(a, Vec2f(2.4f, 2.0f));
    ASSERT_EQ(b, Vec2f(3.4f, 45.0f));

    a += b;
    ASSERT_EQ(a, result);
    ASSERT_EQ(b, Vec2f(3.4f, 45.0f));
}

TEST(Vector2Math, Subtraction) {
    Vec2f a(4.4f, 47.0f);
    Vec2f b(3.4f, 45.0);
    Vec2f result(1.0f, 2.0f);

    ASSERT_EQ(a - b, result);
    ASSERT_EQ(b - a, -result);
    ASSERT_EQ(a, Vec2f(4.4f, 47.0f));
    ASSERT_EQ(b, Vec2f(3.4f, 45.0));

    a -= b;
    ASSERT_EQ(a, result);
    ASSERT_EQ(b, Vec2f(3.4f, 45.0f));
}

TEST(Vector2Math, Multiplication) {
    Vec2f a(5.0f, 1.0f);
    Vec2f b(2.1f, 7.0f);
    Vec2f result(10.5f, 7.0f);

    ASSERT_EQ(a * b, result);
    ASSERT_EQ(b * a, result);
    ASSERT_EQ(a, Vec2f(5.0f, 1.0f));
    ASSERT_EQ(b, Vec2f(2.1f, 7.0f));

    a *= b;
    ASSERT_EQ(a, result);
    ASSERT_EQ(b, Vec2f(2.1f, 7.0f));
}

TEST(Vector2Math, Division) {
    Vec2f a(7.0f, 8.0f);
    Vec2f b(2.0f, 4.0f);
    Vec2f result(3.5f, 2.0f);

    ASSERT_EQ(a / b, result);
    ASSERT_FLOAT_EQ((b / a).x, 0.2857142f);
    ASSERT_EQ((b / a).y, 0.5f);
    ASSERT_EQ(a, Vec2f(7.0f, 8.0f));
    ASSERT_EQ(b, Vec2f(2.0f, 4.0f));

    a /= b;
    ASSERT_EQ(a, result);
    ASSERT_EQ(b, Vec2f(2.0f, 4.0f));
}

TEST(Vector2Math, Negation) {
    Vec2f a(7.0f, -8.0f);
    Vec2f b(-2.0f, 0.0f);

    ASSERT_EQ(-a, Vec2f(-7.0f, 8.0f));
    ASSERT_EQ(-b, Vec2f(2.0f, 0.0f));
}

TEST(Vector2Functions, Absolute) {
    Vec2f a(-5.0f, -3.0f);
    Vec2f b(-1.0f, 2.0f);
    Vec2f c(0.0f, 0.0f);

    ASSERT_EQ(a.abs(), Vec2f(5.0f, 3.0f));
    ASSERT_EQ(b.abs(), Vec2f(1.0f, 2.0f));
    ASSERT_EQ(c.abs(), Vec2f(0.0f, 0.0f));
}

TEST(Vector2Functions, Length) {
    Vec2f a(3.0f, 4.0f);
    Vec2f b(3.8f, 2.3f);
    Vec2f c(23.5f, 12.4f);

    ASSERT_EQ(a.length(), 5);
    ASSERT_FLOAT_EQ(b.length(), 4.4418464f);
    ASSERT_FLOAT_EQ(c.length(), 26.5708486f);
}

TEST(Vector2Functions, Normalization) {
    Vec2f a(2.5f, 1.2f);
    Vec2f b(-1.4f, 3.7f);
    Vec2f c = Vec2f::right;
    Vec2f d = Vec2f::up;
    Vec2f e = Vec2f::left;
    Vec2f f = Vec2f::down;

    Vec2f a_normalized = a.normalize();
    Vec2f b_normalized = b.normalize();

    ASSERT_FLOAT_EQ(a_normalized.x, 0.9015230f);
    ASSERT_FLOAT_EQ(a_normalized.y, 0.4327310f);

    ASSERT_FLOAT_EQ(b_normalized.x, -0.3538920f);
    ASSERT_FLOAT_EQ(b_normalized.y, 0.9352862f);

    ASSERT_EQ(c.normalize(), Vec2f::right);
    ASSERT_EQ(d.normalize(), Vec2f::up);
    ASSERT_EQ(e.normalize(), Vec2f::left);
    ASSERT_EQ(f.normalize(), Vec2f::down);
}

TEST(Vector2Functions, Splat) {
    ASSERT_EQ(Vec2f::splat(1.0f), Vec2f(1.0f, 1.0f));
    ASSERT_EQ(Vec2f::splat(5.0f), Vec2f(5.0f, 5.0f));
}

TEST(Vector2Functions, Dot) {
    Vec2f a(1.3f, 4.5f);
    Vec2f b(2.5f, 3.7f);
    Vec2f c(6.7f, 1.3f);

    ASSERT_FLOAT_EQ(Vec2f::dot(a, b), 19.9f);
    ASSERT_FLOAT_EQ(Vec2f::dot(b, a), 19.9f);
    ASSERT_FLOAT_EQ(Vec2f::dot(b, c), 21.56f);
    ASSERT_FLOAT_EQ(Vec2f::dot(c, b), 21.56f);
}

TEST(Vector2Functions, Projection) {
    Vec2f a(4.0f, 5.0f);
    Vec2f b(3.0f, -3.0f);
    Vec2f c(2.5f, -6.4f);

    ASSERT_EQ(Vec2f::project(a, b), Vec2f(-0.5f, 0.5f));

    ASSERT_FLOAT_EQ(Vec2f::project(b, a).x, -0.2926829f);
    ASSERT_FLOAT_EQ(Vec2f::project(b, a).y, -0.3658536f);

    ASSERT_FLOAT_EQ(Vec2f::project(b, c).x, 1.4138953f);
    ASSERT_FLOAT_EQ(Vec2f::project(b, c).y, -3.6195721f);

    ASSERT_EQ(Vec2f::project(c, b), Vec2f(4.45f, -4.45f));
}

TEST(Vector2Functions, Rejection) {
    Vec2f a(4.0f, 5.0f);
    Vec2f b(3.0f, -3.0f);
    Vec2f c(2.5f, -6.4f);

    ASSERT_EQ(Vec2f::reject(a, b), Vec2f(4.5f, 4.5f));

    ASSERT_FLOAT_EQ(Vec2f::reject(b, a).x, 3.2926829f);
    ASSERT_FLOAT_EQ(Vec2f::reject(b, a).y, -2.6341464f);

    ASSERT_FLOAT_EQ(Vec2f::reject(b, c).x, 1.5861047f);
    ASSERT_FLOAT_EQ(Vec2f::reject(b, c).y, 0.6195721f);

    ASSERT_FLOAT_EQ(Vec2f::reject(c, b).x, -1.95f);
    ASSERT_FLOAT_EQ(Vec2f::reject(c, b).y, -1.95f);
}