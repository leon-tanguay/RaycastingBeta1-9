#include <gtest/gtest.h>
#include "../src/rcvector.h"
#include <array>

using rc::RCVector;

TEST(rcvectorTest, defaultConstructors)
{
    //act
    RCVector<int> rcVec2i;
    RCVector<unsigned int> rcVec2u;
    RCVector<float> rcVec2f;
    RCVector<double> rcVec2d;
    rc::Vector2i vector2i;
    rc::Vector2f vector2f;

    //assert
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

TEST(rcvectorTest, twoValueConstructors)
{
    //act
    RCVector<int> rcVec2i{ 2, 4 };
    RCVector<unsigned int> rcVec2u{ 2u, 4u };
    RCVector<float> rcVec2f{ 2.f, 4.f };
    RCVector<double> rcVec2d{ 2.0, 4.0 };

    //assert
    ASSERT_EQ(rcVec2i.x, 2);
    ASSERT_EQ(rcVec2i.y, 4);

    ASSERT_EQ(rcVec2u.x, 2u);
    ASSERT_EQ(rcVec2u.y, 4u);

    ASSERT_FLOAT_EQ(rcVec2f.x, 2.f);
    ASSERT_FLOAT_EQ(rcVec2f.y, 4.f);

    ASSERT_DOUBLE_EQ(rcVec2d.x, 2.0);
    ASSERT_DOUBLE_EQ(rcVec2d.y, 4.0);
}

TEST(rcvectorTest, equality)
{
    //arrange
    const int x = -1;
    const int y = 3;
    const RCVector<int> vec1{ x, y };
    const RCVector<int> vec2{ x, y };

    //act
    const bool isEqual = (vec1 == vec2);
    const bool isNotEqual = (vec1 != vec2);

    //assert
    EXPECT_TRUE(isEqual);
    EXPECT_FALSE(isNotEqual);
}

TEST(rcvectorTest, inEquality)
{
    //arrange
    const int x = -1;
    const int y = 3;
    const RCVector<int> vec1{ x, y };
    const RCVector<int> vec2{ x+1, y };

    //act
    const bool isEqual = (vec1 == vec2);
    const bool isNotEqual = (vec1 != vec2);

    //assert
    EXPECT_FALSE(isEqual);
    EXPECT_TRUE(isNotEqual);
}

TEST(rcvectorTest, plus)
{
    //arrange
    const std::array<int, 2> x = { 3, 2 };
    const std::array<int, 2> y = { 9, 7 };
    const RCVector<int> lhs{ x[0], y[0] };
    const RCVector<int> rhs{ x[1], y[1] };
    const RCVector<int> truth{ x[0] + x[1], y[0] + y[1] };

    //act
    const RCVector<int> result = lhs + rhs;

    //assert
    ASSERT_EQ(result, truth);
    ASSERT_EQ(result.x, x[0] + x[1]);
    ASSERT_EQ(result.y, y[0] + y[1]);
}

TEST(rcvectorTest, minus)
{
    //arrange
    const std::array<int, 2> x = { 3, 2 };
    const std::array<int, 2> y = { 9, 7 };
    const RCVector<int> lhs{ x[0], y[0] };
    const RCVector<int> rhs{ x[1], y[1] };
    const RCVector<int> truth{ x[0] - x[1], y[0] - y[1] };

    //act
    const RCVector<int> result = lhs - rhs;

    //assert
    ASSERT_EQ(result, truth);
    ASSERT_EQ(result.x, x[0] - x[1]);
    ASSERT_EQ(result.y, y[0] - y[1]);
}

TEST(rcvectorTest, multiplyScalar)
{
    //arrange
    const int scalar = 2;
    const int x = -1;
    const int y = 3;
    const RCVector<int> rcVec2i{ x, y };
    RCVector<int> truth{ x*scalar, y*scalar};

    //act
    RCVector<int> result = rcVec2i * scalar;

    //assert
    ASSERT_EQ(result, truth);
    ASSERT_EQ(result.x, x * scalar);
    ASSERT_EQ(result.y, y * scalar);
}

TEST(rcvectorTest, divideScalar)
{
    //arrange
    const float scalar = 5.f;
    const float x = 2.f;
    const float y = 3.f;
    RCVector<float> rcVec2f{ x, y };

    //act
    RCVector<float> result = rcVec2f / scalar;

    //assert
    ASSERT_FLOAT_EQ(result.x, x / scalar);
    ASSERT_FLOAT_EQ(result.y, y / scalar);
}

TEST(rcvectorTest, plusEquals)
{
    //arrange
    const int scalar = 33;
    std::array<int, 2> x = { 3, 2 };
    std::array<int, 2> y = { 9, 7 };
    const RCVector<int> lhs{ x[0], y[0]};
    const RCVector<int> rhs{ x[1], y[1] };
    RCVector<int> truth2i{ x[0] + x[1], y[0] + y[1] };

    //act
    RCVector<int> result2i = lhs;
    result2i += rhs;

    //assert
    ASSERT_EQ(result2i, truth2i);
}

TEST(rcvectorTest, minusEquals)
{
    //arrange
    const int scalar = 2;
    std::array<int, 2> x = { 3, 2 };
    std::array<int, 2> y = { 9, 7 };
    const RCVector<int> lhs{ x[0], y[0] };
    const RCVector<int> rhs{ x[1], y[1] };
    RCVector<int> truth2i{ x[0] - x[1], y[0] - y[1] };

    //act
    RCVector<int> result2i = lhs;
    result2i -= rhs;

    //assert
    ASSERT_EQ(result2i, truth2i);
}

TEST(rcvectorTest, timesEqualsConst)
{
    //arrange
    const float scalar = 2.5f;
    const float x = 4.2f;
    const float y = 3.1f;

    //act
    RCVector<float> result{ x, y };
    result *= scalar;

    //assert
    ASSERT_FLOAT_EQ(result.x, x * scalar);
    ASSERT_FLOAT_EQ(result.y, y * scalar);
}

TEST(rcvectorTest, dividedByEqualsConst)
{
    //arrange
    const float scalar = 2.5f;
    const float x = 4.2f;
    const float y = 3.1f;

    //act
    RCVector<float> result{ x, y };
    result /= scalar;

    //assert
    ASSERT_FLOAT_EQ(result.x, x / scalar);
    ASSERT_FLOAT_EQ(result.y, y / scalar);
}

TEST(rcvectorTest, magnitude)
{
    //arrange
    const float x = 4.f;
    const float y = 3.f;
    RCVector<float> vector2f{ x, y };
    const float truth = sqrt((x * x) + (y * y));

    //act
    float result = vector2f.magnitude();

    //assert
    ASSERT_EQ(result, truth);
}

TEST(rcvectorTest, unitVector)
{
    //arrange
    const float x = 4.f;
    const float y = 3.f;
    const RCVector<float> vector2f{ x, y };
    const float magnitude = sqrt((x * x) + (y * y));
    const RCVector<float> truth{ x / magnitude, y / magnitude };

    //act
    const RCVector<float> result = vector2f.getUnitVector();

    //assert
    ASSERT_FLOAT_EQ(result.x, truth.x);
    ASSERT_FLOAT_EQ(result.y, truth.y);

}

TEST(rcvectorTest, getPerpVector)
{
    //arrange
    const float x = 4.f;
    const float y = 3.f;
    const RCVector<float> vector2f{ x, y };
    const RCVector<float> truth{ -y, x };

    //act
    const RCVector<float> result = vector2f.getPerpendicularVector();

    //assert
    ASSERT_FLOAT_EQ(result.x, truth.x);
    ASSERT_FLOAT_EQ(result.y, truth.y);
}


TEST(rcvectorTest, getPerpUnitVector)
{
    //arrange
    const float x = 4.f;
    const float y = 3.f;
    const RCVector<float> vector2f{ x, y };
    const float magnitude = sqrt((x * x) + (y * y));
    const RCVector<float> truth{ -y / magnitude, x / magnitude };

    //act
    const RCVector<float> result = vector2f.getPerpendicularUnitVector();

    //assert
    ASSERT_FLOAT_EQ(result.x, truth.x);
    ASSERT_FLOAT_EQ(result.y, truth.y);
}


TEST(rcvectorTest, toInt)
{
    //arrange
    const float x = 4.f;
    const float y = 3.f;
    const RCVector<float> vector2f{ x, y };

    //act
    const RCVector<int> result = vector2f.toInt();

    //assert
    ASSERT_EQ(result.x, static_cast<int>(x));
    ASSERT_EQ(result.y, static_cast<int>(y));
}

TEST(rcvectorTest, toFloat)
{
    //arrange
    const int x = 4;
    const int y = 3;
    const RCVector<int> vector2f{ x, y };

    //act
    const RCVector<float> result = vector2f.toFloat();

    //assert
    ASSERT_EQ(result.x, static_cast<float>(x));
    ASSERT_EQ(result.y, static_cast<float>(y));
}