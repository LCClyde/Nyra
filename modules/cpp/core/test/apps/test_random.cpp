/*
 * Copyright (c) 2017 Clyde Stanfield
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
#include <nyra/core/Random.h>
#include <nyra/test/Test.h>

namespace
{
//===========================================================================//
template <typename T>
double mean(std::vector<T>& vec)
{
    T sum = 0;
    for (auto val : vec)
    {
        sum += val;
    }

    return sum / static_cast<double>(vec.size());
}

//===========================================================================//
template <typename T>
double stdDev(std::vector<T>& vec)
{
    const double mean_ = mean(vec);
    std::vector<double> v2;
    for (auto v : vec)
    {
        const double diff = mean_ - v;
        v2.push_back(diff * diff);
    }
    return std::sqrt(mean(v2));
}
}

//===========================================================================//
namespace nyra
{
namespace core
{
//===========================================================================//
TEST(Random, UniformSeed)
{
    RandomUniform<double> s0(0);
    RandomUniform<double> s1(0);
    RandomUniform<double> s2;

    std::vector<double> r0;
    std::vector<double> r1;
    std::vector<double> r2;

    for (size_t ii = 0; ii < 100; ++ii)
    {
        r0.push_back(s0());
        r1.push_back(s1());
        r2.push_back(s2());
    }

    for (size_t ii = 0; ii < r0.size(); ++ii)
    {
        EXPECT_EQ(r0[ii], r1[ii]);
        EXPECT_NE(r0[ii], r2[ii]);
    }
}

//===========================================================================//
TEST(Random, NormalSeed)
{
    RandomNormal<double> s0(0);
    RandomNormal<double> s1(0);
    RandomNormal<double> s2;

    std::vector<double> r0;
    std::vector<double> r1;
    std::vector<double> r2;

    for (size_t ii = 0; ii < 100; ++ii)
    {
        r0.push_back(s0());
        r1.push_back(s1());
        r2.push_back(s2());
    }

    for (size_t ii = 0; ii < r0.size(); ++ii)
    {
        EXPECT_EQ(r0[ii], r1[ii]);
        EXPECT_NE(r0[ii], r2[ii]);
    }
}

//===========================================================================//
TEST(Random, UniformDistribution)
{
    RandomUniform<double> s0(0, 0, 10);
    std::vector<int32_t> bins(10);
    std::vector<double> binSorter =
            {1.0, 2.0, 3.0, 4.0, 5.0,
             6.0, 7.0, 8.0, 9.0, 10.0};

    for (size_t ii = 0; ii < 10000; ++ii)
    {
        const double value = s0();
        for (size_t jj = 0; jj < binSorter.size(); ++jj)
        {
            if (value < binSorter[jj])
            {
                bins[jj]++;
                break;
            }
        }
    }

    for (size_t ii = 0; ii < bins.size(); ++ii)
    {
        // We expect about 1000 values in each bin +- 100.
        EXPECT_NEAR(1000, bins[ii], 100);
    }

}

//===========================================================================//
TEST(Random, NormalRealDistribution)
{
    RandomNormal<double> s0(0, 100.0, 5.0);
    std::vector<double> results;

    for (size_t ii = 0; ii < 10000; ++ii)
    {
        results.push_back(s0());
    }

    // The mean should be close to 100
    EXPECT_NEAR(100.0, mean(results), 0.1);
    EXPECT_NEAR(5.0, stdDev(results), 0.1);
}

//===========================================================================//
TEST(Random, NormalIntDistribution)
{
    RandomNormal<int32_t> s0(0, 100, 5);
    std::vector<int32_t> results;

    for (size_t ii = 0; ii < 10000; ++ii)
    {
        results.push_back(s0());
    }

    // The mean should be close to 100
    EXPECT_NEAR(100.0, mean(results), 0.1);
    EXPECT_NEAR(5.0, stdDev(results), 0.1);
}

//===========================================================================//
TEST(Random, UniformRealMinMax)
{
    RandomUniform<double> s0(0, -2.5, 6.0);

    for (size_t ii = 0; ii < 1000; ++ii)
    {
        const double value = s0();
        EXPECT_GT(value, -2.5);
        EXPECT_LT(value, 6.0);
    }
}

//===========================================================================//
TEST(Random, UniformIntMinMax)
{
    RandomUniform<int32_t> s0(0, -20, 60);

    for (size_t ii = 0; ii < 1000; ++ii)
    {
        const int32_t value = s0();
        EXPECT_GE(value, -20);
        EXPECT_LE(value, 60);
    }
}

//===========================================================================//
TEST(Random, NormalRealMinMax)
{
    RandomNormal<double> s0(0, 0.0, 1.0, -1.5, 1.5);

    for (size_t ii = 0; ii < 1000; ++ii)
    {
        const double value = s0();
        EXPECT_GT(value, -1.5);
        EXPECT_LT(value, 1.5);
    }
}

//===========================================================================//
TEST(Random, NormalIntMinMax)
{
    RandomNormal<int32_t> s0(0, 0, 10, -15, 15);

    for (size_t ii = 0; ii < 1000; ++ii)
    {
        const int32_t value = s0();
        EXPECT_GE(value, -15);
        EXPECT_LE(value, 15);
    }
}
}
}

NYRA_TEST()
