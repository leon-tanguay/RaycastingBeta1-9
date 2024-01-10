#include <gtest/gtest.h>
#include "../src/rcvector.h"

using rc::RCVector;

TEST(rcvectorTest, defaultConstructors)
{
    RCVector<int> rcVec2i;
    RCVector<unsigned int> rcVec2u;
    RCVector<float> rcVec2f;
    RCVector<double> rcVec2d;
    rc::Vector2i vector2i;
    rc::Vector2f vector2f;

    ASSERT_EQ(rcVec2i.x, 0);
    ASSERT_EQ(rcVec2i.y, 0);

    ASSERT_EQ(rcVec2u.x, 0u);
    ASSERT_EQ(rcVec2u.y, 0u);

    ASSERT_FLOAT_EQ(rcVec2f.x, 0.f);
    ASSERT_FLOAT_EQ(rcVec2f.y, 0.f);

    ASSERT_DOUBLE_EQ(rcVec2d.x, 0.0);
    ASSERT_DOUBLE_EQ(rcVec2d.y, 0.0);

    ASSERT_EQ(vector2i.x, 0);
    ASSERT_EQ(vector2i.y, 0);

    ASSERT_FLOAT_EQ(vector2f.x, 0.f);
    ASSERT_FLOAT_EQ(vector2f.y, 0.f);
}

TEST(rcvectorTest, plus)
{
    RCVector<int> rcVec2i (1,2);
    RCVector<unsigned int> rcVec2u(1u, 2u);
    RCVector<float> rcVec2f(1.f, 2.f);
    RCVector<double> rcVec2d(1.0, 2.0);
    rc::Vector2i vector2i(1, 2);
    rc::Vector2f vector2f(1, 2);

    ASSERT_EQ((rcVec2i + rcVec2i).x, 2);
    ASSERT_EQ((rcVec2i + rcVec2i).y, 4);

    ASSERT_EQ((rcVec2u + rcVec2u).x, 2u);
    ASSERT_EQ((rcVec2u + rcVec2u).y, 4u);

    ASSERT_EQ((rcVec2f + rcVec2f).x, 2.f);
    ASSERT_EQ((rcVec2f + rcVec2f).y, 4.f);

    ASSERT_EQ((rcVec2d + rcVec2d).x, 2.0);
    ASSERT_EQ((rcVec2d + rcVec2d).y, 4.0);

    ASSERT_EQ((vector2i + vector2i).x, 2);
    ASSERT_EQ((vector2i + vector2i).y, 4);

    ASSERT_EQ((vector2f + vector2f).x, 2.f);
    ASSERT_EQ((vector2f + vector2f).y, 4.f);
}

TEST(rcvectorTest, minus)
{
    RCVector<int> rcVec2i(1, 2);
    RCVector<unsigned int> rcVec2u(1u, 2u);
    RCVector<float> rcVec2f(1.f, 2.f);
    RCVector<double> rcVec2d(1.0, 2.0);
    rc::Vector2i vector2i(1, 2);
    rc::Vector2f vector2f(1, 2);

    ASSERT_EQ((rcVec2i - rcVec2i).x, 0);
    ASSERT_EQ((rcVec2i - rcVec2i).y, 0);

    ASSERT_EQ((rcVec2u - rcVec2u).x, 0u);
    ASSERT_EQ((rcVec2u - rcVec2u).y, 0u);

    ASSERT_EQ((rcVec2f - rcVec2f).x, 0.f);
    ASSERT_EQ((rcVec2f - rcVec2f).y, 0.f);

    ASSERT_EQ((rcVec2d - rcVec2d).x, 0.0);
    ASSERT_EQ((rcVec2d - rcVec2d).y, 0.0);

    ASSERT_EQ((vector2i - vector2i).x, 0);
    ASSERT_EQ((vector2i - vector2i).y, 0);

    ASSERT_EQ((vector2f - vector2f).x, 0.f);
    ASSERT_EQ((vector2f - vector2f).y, 0.f);
}

TEST(rcvectorTest, timesConst)
{
    const int n = 2;
    RCVector<int> rcVec2i(1, 2);
    RCVector<unsigned int> rcVec2u(1u, 2u);
    RCVector<float> rcVec2f(1.f, 2.f);
    RCVector<double> rcVec2d(1.0, 2.0);
    rc::Vector2i vector2i(1, 2);
    rc::Vector2f vector2f(1.f, 2.f);

    ASSERT_EQ((rcVec2i * n).x, 2);
    ASSERT_EQ((rcVec2i * n).y, 4);

    ASSERT_EQ((rcVec2u * n).x, 2u);
    ASSERT_EQ((rcVec2u * n).y, 4u);

    ASSERT_EQ((rcVec2f * n).x, 2.f);
    ASSERT_EQ((rcVec2f * n).y, 4.f);

    ASSERT_EQ((rcVec2d * n).x, 2.0);
    ASSERT_EQ((rcVec2d * n).y, 4.0);

    ASSERT_EQ((vector2i * n).x, 2);
    ASSERT_EQ((vector2i * n).y, 4);

    ASSERT_EQ((vector2f * n).x, 2.f);
    ASSERT_EQ((vector2f * n).y, 4.f);
}

TEST(rcvectorTest, dividedByConst)
{
    const int n = 2;
    RCVector<int> rcVec2i(2, 4);
    RCVector<unsigned int> rcVec2u(2u, 4u);
    RCVector<float> rcVec2f(2.f, 4.f);
    RCVector<double> rcVec2d(2.0, 4.0);
    rc::Vector2i vector2i(2, 4);
    rc::Vector2f vector2f(2.f, 4.f);

    ASSERT_EQ((rcVec2i / n).x, 1);
    ASSERT_EQ((rcVec2i / n).y, 2);

    ASSERT_EQ((rcVec2u / n).x, 1u);
    ASSERT_EQ((rcVec2u / n).y, 2u);

    ASSERT_EQ((rcVec2f / n).x, 1.f);
    ASSERT_EQ((rcVec2f / n).y, 2.f);

    ASSERT_EQ((rcVec2d / n).x, 1.0);
    ASSERT_EQ((rcVec2d / n).y, 2.0);

    ASSERT_EQ((vector2i / n).x, 1);
    ASSERT_EQ((vector2i / n).y, 2);

    ASSERT_EQ((vector2f / n).x, 1.f);
    ASSERT_EQ((vector2f / n).y, 2.f);
}

TEST(rcvectorTest, plusEquals)
{
    RCVector<int> rcVec2i(2, 2);
    RCVector<int> rcVec2i_2(3, 3);

    RCVector<unsigned int> rcVec2u(2u, 2u);
    RCVector<unsigned int> rcVec2u_2(3u, 3u);

    RCVector<float> rcVec2f(2.f, 2.f);
    RCVector<float> rcVec2f_2(3.f, 3.f);

    RCVector<double> rcVec2d(2.0, 2.0);
    RCVector<double> rcVec2d_2(3.0, 3.0);

    rc::Vector2i vector2i(2, 2);
    rc::Vector2i vector2i_2(3, 3);

    rc::Vector2f vector2f(2.f, 2.f);
    rc::Vector2f vector2f_2(3.f, 3.f);

    ASSERT_EQ(rcVec2i.x, 2);
    ASSERT_EQ(rcVec2i.y, 2);

    ASSERT_EQ(rcVec2u.x, 2u);
    ASSERT_EQ(rcVec2u.y, 2u);

    ASSERT_FLOAT_EQ(rcVec2f.x, 2.f);
    ASSERT_FLOAT_EQ(rcVec2f.y, 2.f);

    ASSERT_DOUBLE_EQ(rcVec2d.x, 2.0);
    ASSERT_DOUBLE_EQ(rcVec2d.y, 2.0);

    ASSERT_EQ(vector2i.x, 2);
    ASSERT_EQ(vector2i.y, 2);

    ASSERT_FLOAT_EQ(vector2f.x, 2.f);
    ASSERT_FLOAT_EQ(vector2f.y, 2.f);

    rcVec2i += rcVec2i_2;
    rcVec2u += rcVec2u_2;
    rcVec2f += rcVec2f_2;
    rcVec2d += rcVec2d_2;
    vector2i += vector2i_2;
    vector2f += vector2f_2;

    //should be changed
    ASSERT_EQ(rcVec2i.x, 5);
    ASSERT_EQ(rcVec2i.y, 5);

    ASSERT_EQ(rcVec2u.x, 5u);
    ASSERT_EQ(rcVec2u.y, 5u);

    ASSERT_FLOAT_EQ(rcVec2f.x, 5.f);
    ASSERT_FLOAT_EQ(rcVec2f.y, 5.f);

    ASSERT_DOUBLE_EQ(rcVec2d.x, 5.0);
    ASSERT_DOUBLE_EQ(rcVec2d.y, 5.0);

    ASSERT_EQ(vector2i.x, 5);
    ASSERT_EQ(vector2i.y, 5);

    ASSERT_FLOAT_EQ(vector2f.x, 5.f);
    ASSERT_FLOAT_EQ(vector2f.y, 5.f);

    //should be unchanged
    ASSERT_EQ(rcVec2i_2.x, 3);
    ASSERT_EQ(rcVec2i_2.y, 3);

    ASSERT_EQ(rcVec2u_2.x, 3u);
    ASSERT_EQ(rcVec2u_2.y, 3u);

    ASSERT_FLOAT_EQ(rcVec2f_2.x, 3.f);
    ASSERT_FLOAT_EQ(rcVec2f_2.y, 3.f);

    ASSERT_DOUBLE_EQ(rcVec2d_2.x, 3.0);
    ASSERT_DOUBLE_EQ(rcVec2d_2.y, 3.0);

    ASSERT_EQ(vector2i_2.x, 3);
    ASSERT_EQ(vector2i_2.y, 3);

    ASSERT_FLOAT_EQ(vector2f_2.x, 3.f);
    ASSERT_FLOAT_EQ(vector2f_2.y, 3.f);
}

TEST(rcvectorTest, minusEquals)
{
    RCVector<int> rcVec2i(2, 2);
    RCVector<int> rcVec2i_2(3, 3);

    RCVector<unsigned int> rcVec2u(2u, 2u);
    RCVector<unsigned int> rcVec2u_2(3u, 3u);

    RCVector<float> rcVec2f(2.f, 2.f);
    RCVector<float> rcVec2f_2(3.f, 3.f);

    RCVector<double> rcVec2d(2.0, 2.0);
    RCVector<double> rcVec2d_2(3.0, 3.0);

    rc::Vector2i vector2i(2, 2);
    rc::Vector2i vector2i_2(3, 3);

    rc::Vector2f vector2f(2.f, 2.f);
    rc::Vector2f vector2f_2(3.f, 3.f);

    ASSERT_EQ(rcVec2i_2.x, 3);
    ASSERT_EQ(rcVec2i_2.y, 3);

    ASSERT_EQ(rcVec2u_2.x, 3u);
    ASSERT_EQ(rcVec2u_2.y, 3u);

    ASSERT_FLOAT_EQ(rcVec2f_2.x, 3.f);
    ASSERT_FLOAT_EQ(rcVec2f_2.y, 3.f);

    ASSERT_DOUBLE_EQ(rcVec2d_2.x, 3.0);
    ASSERT_DOUBLE_EQ(rcVec2d_2.y, 3.0);

    ASSERT_EQ(vector2i_2.x, 3);
    ASSERT_EQ(vector2i_2.y, 3);

    ASSERT_FLOAT_EQ(vector2f_2.x, 3.f);
    ASSERT_FLOAT_EQ(vector2f_2.y, 3.f);

    rcVec2i_2 -= rcVec2i;
    rcVec2u_2 -= rcVec2u;
    rcVec2f_2 -= rcVec2f;
    rcVec2d_2 -= rcVec2d;
    vector2i_2 -= vector2i;
    vector2f_2 -= vector2f;

    //should be changed
    ASSERT_EQ(rcVec2i_2.x, 1);
    ASSERT_EQ(rcVec2i_2.y, 1);

    ASSERT_EQ(rcVec2u_2.x, 1u);
    ASSERT_EQ(rcVec2u_2.y, 1u);

    ASSERT_FLOAT_EQ(rcVec2f_2.x, 1.f);
    ASSERT_FLOAT_EQ(rcVec2f_2.y, 1.f);

    ASSERT_DOUBLE_EQ(rcVec2d_2.x, 1.0);
    ASSERT_DOUBLE_EQ(rcVec2d_2.y, 1.0);

    ASSERT_EQ(vector2i_2.x, 1);
    ASSERT_EQ(vector2i_2.y, 1);

    ASSERT_FLOAT_EQ(vector2f_2.x, 1.f);
    ASSERT_FLOAT_EQ(vector2f_2.y, 1.f);

    //should be unchanged
    ASSERT_EQ(rcVec2i.x, 2);
    ASSERT_EQ(rcVec2i.y, 2);

    ASSERT_EQ(rcVec2u.x, 2u);
    ASSERT_EQ(rcVec2u.y, 2u);

    ASSERT_FLOAT_EQ(rcVec2f.x, 2.f);
    ASSERT_FLOAT_EQ(rcVec2f.y, 2.f);

    ASSERT_DOUBLE_EQ(rcVec2d.x, 2.0);
    ASSERT_DOUBLE_EQ(rcVec2d.y, 2.0);

    ASSERT_EQ(vector2i.x, 2);
    ASSERT_EQ(vector2i.y, 2);

    ASSERT_FLOAT_EQ(vector2f.x, 2.f);
    ASSERT_FLOAT_EQ(vector2f.y, 2.f);
}

TEST(rcvectorTest, timesEqualsConst)
{
    const int n = 2;

    RCVector<int> rcVec2i(1, 2);
    RCVector<unsigned int> rcVec2u(1u, 2u);
    RCVector<float> rcVec2f(1.f, 2.f);
    RCVector<double> rcVec2d(1.0, 2.0);
    rc::Vector2i vector2i(1, 2);
    rc::Vector2f vector2f(1, 2);

    ASSERT_EQ(rcVec2i.x, 1);
    ASSERT_EQ(rcVec2i.y, 2);

    ASSERT_EQ(rcVec2u.x, 1u);
    ASSERT_EQ(rcVec2u.y, 2u);

    ASSERT_FLOAT_EQ(rcVec2f.x, 1.f);
    ASSERT_FLOAT_EQ(rcVec2f.y, 2.f);

    ASSERT_DOUBLE_EQ(rcVec2d.x, 1.0);
    ASSERT_DOUBLE_EQ(rcVec2d.y, 2.0);

    ASSERT_EQ(vector2i.x, 1);
    ASSERT_EQ(vector2i.y, 2);

    ASSERT_FLOAT_EQ(vector2f.x, 1.f);
    ASSERT_FLOAT_EQ(vector2f.y, 2.f);

    rcVec2i *= n;
    rcVec2u *= n;
    rcVec2f *= n;
    rcVec2d *= n;
    vector2i *= n;
    vector2f *= n;

    ASSERT_EQ(rcVec2i.x, 2);
    ASSERT_EQ(rcVec2i.y, 4);

    ASSERT_EQ(rcVec2u.x, 2u);
    ASSERT_EQ(rcVec2u.y, 4u);

    ASSERT_FLOAT_EQ(rcVec2f.x, 2.f);
    ASSERT_FLOAT_EQ(rcVec2f.y, 4.f);

    ASSERT_DOUBLE_EQ(rcVec2d.x, 2.0);
    ASSERT_DOUBLE_EQ(rcVec2d.y, 4.0);

    ASSERT_EQ(vector2i.x, 2);
    ASSERT_EQ(vector2i.y, 4);

    ASSERT_FLOAT_EQ(vector2f.x, 2.f);
    ASSERT_FLOAT_EQ(vector2f.y, 4.f);
}

TEST(rcvectorTest, dividedByEqualsConst)
{
    const int n = 3;

    RCVector<int> rcVec2i(3, 9);
    RCVector<unsigned int> rcVec2u(3u, 9u);
    RCVector<float> rcVec2f(3.f, 9.f);
    RCVector<double> rcVec2d(3.0, 9.0);
    rc::Vector2i vector2i(3, 9);
    rc::Vector2f vector2f(3, 9);

    ASSERT_EQ(rcVec2i.x, 3);
    ASSERT_EQ(rcVec2i.y, 9);

    ASSERT_EQ(rcVec2u.x, 3u);
    ASSERT_EQ(rcVec2u.y, 9u);

    ASSERT_FLOAT_EQ(rcVec2f.x, 3.f);
    ASSERT_FLOAT_EQ(rcVec2f.y, 9.f);

    ASSERT_DOUBLE_EQ(rcVec2d.x, 3.0);
    ASSERT_DOUBLE_EQ(rcVec2d.y, 9.0);

    ASSERT_EQ(vector2i.x, 3);
    ASSERT_EQ(vector2i.y, 9);

    ASSERT_FLOAT_EQ(vector2f.x, 3.f);
    ASSERT_FLOAT_EQ(vector2f.y, 9.f);

    rcVec2i /= n;
    rcVec2u /= n;
    rcVec2f /= n;
    rcVec2d /= n;
    vector2i /= n;
    vector2f /= n;

    ASSERT_EQ(rcVec2i.x, 1);
    ASSERT_EQ(rcVec2i.y, 3);

    ASSERT_EQ(rcVec2u.x, 1u);
    ASSERT_EQ(rcVec2u.y, 3u);

    ASSERT_FLOAT_EQ(rcVec2f.x, 1.f);
    ASSERT_FLOAT_EQ(rcVec2f.y, 3.f);

    ASSERT_DOUBLE_EQ(rcVec2d.x, 1.0);
    ASSERT_DOUBLE_EQ(rcVec2d.y, 3.0);

    ASSERT_EQ(vector2i.x, 1);
    ASSERT_EQ(vector2i.y, 3);

    ASSERT_FLOAT_EQ(vector2f.x, 1.f);
    ASSERT_FLOAT_EQ(vector2f.y, 3.f);
}

TEST(rcvectorTest, magnitude)
{
    RCVector<int> rcVec2i(4, 3);
    RCVector<unsigned int> rcVec2u(4u, 3u);
    RCVector<float> rcVec2f(4.f, 3.f);
    RCVector<double> rcVec2d(4.0, 3.0);
    rc::Vector2i vector2i(4, 3);
    rc::Vector2f vector2f(4.f, 3.f);

    ASSERT_EQ(rcVec2i.magnitude(), 5.f);

    ASSERT_EQ(rcVec2u.magnitude(), 5.f);

    ASSERT_EQ(rcVec2f.magnitude(), 5.f);

    ASSERT_EQ(rcVec2d.magnitude(), 5.f);

    ASSERT_EQ(vector2i.magnitude(), 5.f);

    ASSERT_EQ(vector2f.magnitude(), 5.f);
}

TEST(rcvectorTest, unitVector)
{
    RCVector<int> rcVec2i(2, 2);
    RCVector<unsigned int> rcVec2u(2u, 2u);
    RCVector<float> rcVec2f(2.f, 2.f);
    RCVector<double> rcVec2d(2.0, 2.0);
    rc::Vector2i vector2i(2, 2);
    rc::Vector2f vector2f(2.f, 2.f);

    ASSERT_TRUE(abs(rcVec2i.getUnitVector().x - sqrtf(2) / 2.f) < 0.001);
    ASSERT_TRUE(abs(rcVec2i.getUnitVector().y - sqrtf(2) / 2.f) < 0.001);

    ASSERT_TRUE(abs(rcVec2u.getUnitVector().x - sqrtf(2) / 2.f) < 0.001);
    ASSERT_TRUE(abs(rcVec2u.getUnitVector().y - sqrtf(2) / 2.f) < 0.001);

    ASSERT_TRUE(abs(rcVec2f.getUnitVector().x - sqrtf(2) / 2.f) < 0.001);
    ASSERT_TRUE(abs(rcVec2f.getUnitVector().y - sqrtf(2) / 2.f) < 0.001);

    ASSERT_TRUE(abs(rcVec2d.getUnitVector().x - sqrtf(2) / 2.f) < 0.001);
    ASSERT_TRUE(abs(rcVec2d.getUnitVector().y - sqrtf(2) / 2.f) < 0.001);

    ASSERT_TRUE(abs(vector2i.getUnitVector().x - sqrtf(2) / 2.f) < 0.001);
    ASSERT_TRUE(abs(vector2i.getUnitVector().y - sqrtf(2) / 2.f) < 0.001);

    ASSERT_TRUE(abs(vector2f.getUnitVector().x - sqrtf(2) / 2.f) < 0.001);
    ASSERT_TRUE(abs(vector2f.getUnitVector().y - sqrtf(2) / 2.f) < 0.001);
}

TEST(rcvectorTest, getPerpVector)
{
    RCVector<int> rcVec2i(4, 3);
    RCVector<unsigned int> rcVec2u(4u, 3u);
    RCVector<float> rcVec2f(4.f, 3.f);
    RCVector<double> rcVec2d(4.0, 3.0);
    rc::Vector2i vector2i(4, 3);
    rc::Vector2f vector2f(4.f, 3.f);

    ASSERT_EQ(rcVec2i.getPerpendicularVector().x, -3);
    ASSERT_EQ(rcVec2i.getPerpendicularVector().y, 4);

    //will not work on a unsigned vector
    //ASSERT_EQ(rcVec2u.getPerpendicularVector().x, 3);
    //ASSERT_EQ(rcVec2u.getPerpendicularVector().y, 4);

    ASSERT_EQ(rcVec2f.getPerpendicularVector().x, -3.f);
    ASSERT_EQ(rcVec2f.getPerpendicularVector().y, 4.f);

    ASSERT_EQ(rcVec2d.getPerpendicularVector().x, -3.0);
    ASSERT_EQ(rcVec2d.getPerpendicularVector().y, 4.0);

    ASSERT_EQ(vector2i.getPerpendicularVector().x, -3);
    ASSERT_EQ(vector2i.getPerpendicularVector().y, 4);

    ASSERT_EQ(vector2f.getPerpendicularVector().x, -3.f);
    ASSERT_EQ(vector2f.getPerpendicularVector().y, 4.f);
}

/*
TEST(rcvectorTest, getPerpUnitVector)
{
    RCVector<int> rcVec2i(2, 2);
    RCVector<unsigned int> rcVec2u(2u, 2u);
    RCVector<float> rcVec2f(2.f, 2.f);
    RCVector<double> rcVec2d(2.0, 2.0);
    rc::Vector2i vector2i(2, 2);
    rc::Vector2f vector2f(2.f, 2.f);

    ASSERT_TRUE(abs(rcVec2i.getPerpendicularUnitVector().x + sqrtf(2) / 2.f) < 0.001);
    ASSERT_TRUE(abs(rcVec2i.getPerpendicularUnitVector().y - sqrtf(2) / 2.f) < 0.001);

    ASSERT_TRUE(abs(rcVec2u.getPerpendicularUnitVector().x + sqrtf(2) / 2.f) < 0.001);
    ASSERT_TRUE(abs(rcVec2u.getPerpendicularUnitVector().y - sqrtf(2) / 2.f) < 0.001);

    ASSERT_TRUE(abs(rcVec2f.getPerpendicularUnitVector().x + sqrtf(2) / 2.f) < 0.001);
    ASSERT_TRUE(abs(rcVec2f.getPerpendicularUnitVector().y - sqrtf(2) / 2.f) < 0.001);

    ASSERT_TRUE(abs(rcVec2d.getPerpendicularUnitVector().x + sqrtf(2) / 2.f) < 0.001);
    ASSERT_TRUE(abs(rcVec2d.getPerpendicularUnitVector().y - sqrtf(2) / 2.f) < 0.001);

    ASSERT_TRUE(abs(vector2i.getPerpendicularUnitVector().x + sqrtf(2) / 2.f) < 0.001);
    ASSERT_TRUE(abs(vector2i.getPerpendicularUnitVector().y - sqrtf(2) / 2.f) < 0.001);

    ASSERT_TRUE(abs(vector2f.getPerpendicularUnitVector().x + sqrtf(2) / 2.f) < 0.001);
    ASSERT_TRUE(abs(vector2f.getPerpendicularUnitVector().y - sqrtf(2) / 2.f) < 0.001);
}
*/