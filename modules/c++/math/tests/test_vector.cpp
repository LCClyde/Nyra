/*
 * Copyright (c) 2016 Clyde Stanfield
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 *  of this software and associated documentation files (the "Software"), to
 * deal in the Software without restriction, including without limitation the
 * rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 */
#include <gtest/gtest.h>
#include <nyra/math/Vector2.h>

namespace
{
struct ThirdParty
{
public:
    float x;
    float y;
};
}

TEST(Vector2Test, Construction)
{
    // Default construction should 0 values
    {
        const nyra::Vector2F vecF;
        EXPECT_EQ(vecF.x, 0.0f);
        EXPECT_EQ(vecF.y, 0.0f);
        const nyra::Vector2D vecD;
        EXPECT_EQ(vecD.x, 0.0f);
        EXPECT_EQ(vecD.y, 0.0f);
        const nyra::Vector2I vecI;
        EXPECT_EQ(vecI.x, 0);
        EXPECT_EQ(vecI.y, 0);
        const nyra::Vector2U VecU;
        EXPECT_EQ(VecU.x, 0);
        EXPECT_EQ(VecU.y, 0);
    }

    // x, y construction should assign values
    {
        const nyra::Vector2F vecF(5.67f, 1.23f);
        EXPECT_EQ(vecF.x, 5.67f);
        EXPECT_EQ(vecF.y, 1.23f);
        const nyra::Vector2D vecD(5.67f, 1.23f);
        EXPECT_EQ(vecD.x, 5.67f);
        EXPECT_EQ(vecD.y, 1.23f);
        const nyra::Vector2I vecI(-345, 987);
        EXPECT_EQ(vecI.x, -345);
        EXPECT_EQ(vecI.y, 987);
        const nyra::Vector2U VecU(246, 357);
        EXPECT_EQ(VecU.x, 246);
        EXPECT_EQ(VecU.y, 357);
    }

    // Copy construction
    {
        const nyra::Vector2F vecCopy(33.678f, -21.456f);
        const nyra::Vector2F vecF(vecCopy);
        EXPECT_NEAR(vecF.x, 33.678f, 0.0001);
        EXPECT_NEAR(vecF.y, -21.456f, 0.0001);
        const nyra::Vector2D VecD(vecCopy);
        EXPECT_NEAR(VecD.x, 33.678, 0.0001);
        EXPECT_NEAR(VecD.y, -21.456, 0.0001);
        const nyra::Vector2I vecI(vecCopy);
        EXPECT_EQ(vecI.x, 33);
        EXPECT_EQ(vecI.y, -21);
        const nyra::Vector2U VecU(vecCopy);
        EXPECT_EQ(VecU.x, 33);
        EXPECT_EQ(VecU.y, static_cast<uint32_t>(-21));
    }

    // Third party construction
    {
        ThirdParty vecCopy;
        vecCopy.x = 33.678f;
        vecCopy.y = -21.456f;
        const nyra::Vector2F vecF(vecCopy);
        EXPECT_NEAR(vecF.x, 33.678f, 0.0001);
        EXPECT_NEAR(vecF.y, -21.456f, 0.0001);
        const nyra::Vector2D VecD(vecCopy);
        EXPECT_NEAR(VecD.x, 33.678, 0.0001);
        EXPECT_NEAR(VecD.y, -21.456, 0.0001);
        const nyra::Vector2I vecI(vecCopy);
        EXPECT_EQ(vecI.x, 33);
        EXPECT_EQ(vecI.y, -21);
        const nyra::Vector2U VecU(vecCopy);
        EXPECT_EQ(VecU.x, 33);
        EXPECT_EQ(VecU.y, static_cast<uint32_t>(-21));
    }
}

TEST(Vector2Test, Equality)
{
    // Equality
    const nyra::Vector2F vec(4.25f, 9.75f);
    EXPECT_TRUE(vec == vec);
    EXPECT_TRUE(vec == nyra::Vector2F(4.25f, 9.75f));
    EXPECT_FALSE(vec == nyra::Vector2F(0.0f, 0.0f));
    EXPECT_FALSE(vec == nyra::Vector2F(4.25f, 0.0f));
    EXPECT_FALSE(vec == nyra::Vector2F(0.0f, 9.75f));

    // Inequality
    EXPECT_FALSE(vec != vec);
    EXPECT_FALSE(vec != nyra::Vector2F(4.25f, 9.75f));
    EXPECT_TRUE(vec != nyra::Vector2F(0.0f, 0.0f));
    EXPECT_TRUE(vec != nyra::Vector2F(4.25f, 0.0f));
    EXPECT_TRUE(vec != nyra::Vector2F(0.0f, 9.75f));
}

TEST(Vector2Test, Assignment)
{
    nyra::Vector2F vec(10.0f, 20.0f);
    const nyra::Vector2F assigned = vec;
    EXPECT_EQ(assigned, vec);
    vec += vec;
    EXPECT_EQ(vec, nyra::Vector2F(20.0f, 40.0f));
    vec -= assigned;
    EXPECT_EQ(vec, nyra::Vector2F(10.0f, 20.0f));
    vec *= assigned;
    EXPECT_EQ(vec, nyra::Vector2F(100.0f, 400.0f));
    vec /= assigned;
    EXPECT_EQ(vec, nyra::Vector2F(10.0f, 20.0f));
    vec *= 2.0;
    EXPECT_EQ(vec, nyra::Vector2F(20.0f, 40.0f));
    vec /= 2.0;
    EXPECT_EQ(vec, nyra::Vector2F(10.0f, 20.0f));
    vec += 10.0;
    EXPECT_EQ(vec, nyra::Vector2F(20.0f, 30.0f));
    vec -= 10.0;
    EXPECT_EQ(vec, nyra::Vector2F(10.0f, 20.0f));
}

TEST(Vector2Test, Operators)
{
    const nyra::Vector2F vec(10.0f, 20.0f);
    EXPECT_EQ(vec + vec, nyra::Vector2F(20.0f, 40.0f));
    EXPECT_EQ(vec - vec, nyra::Vector2F(0.0f, 0.0f));
    EXPECT_EQ(vec * vec, nyra::Vector2F(100.0f, 400.0f));
    EXPECT_EQ(vec / nyra::Vector2F(2.0f, 4.0f), nyra::Vector2F(5.0f, 5.0f));
    EXPECT_EQ(vec + 10.0, nyra::Vector2F(20.0f, 30.0f));
    EXPECT_EQ(vec - 10.0, nyra::Vector2F(0.0f, 10.0f));
    EXPECT_EQ(vec * 2.0, nyra::Vector2F(20.0f, 40.0f));
    EXPECT_EQ(vec / 2.0, nyra::Vector2F(5.0f, 10.0f));
}

TEST(Vector2Test, Calculations)
{
    nyra::Vector2F vec(10.0f, 20.0f);
    EXPECT_EQ(vec.sum(), 30.0f);
    EXPECT_EQ(vec.product(), 200.0f);
    EXPECT_EQ(vec.sumSquares(), 500.0f);
    EXPECT_DOUBLE_EQ(vec.length(), 22.360679774997898);
    EXPECT_DOUBLE_EQ(vec.lengthSquared(), 500.0f);
    vec.normalize();
    EXPECT_FLOAT_EQ(vec.length(), 1.0f);
}

TEST(Vector2Test, 3rdParty)
{
    const nyra::Vector2F vec(10.25f, 20.67f);
    ThirdParty thirdParty(vec.toThirdParty<ThirdParty>());
    EXPECT_EQ(thirdParty.x, vec.x);
    EXPECT_EQ(thirdParty.y, vec.y);
}

int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
