/*
 * Copyright (c) 2017 Clyde Stanfield
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to
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
#ifndef __NYRA_CORE_RANDOM_H__
#define __NYRA_CORE_RANDOM_H__

#include <random>
#include <nyra/core/Time.h>

namespace nyra
{
namespace core
{
/*
 *  \type GeneratorT
 *  \brief For internal use to control the global generator.
 */
typedef std::mt19937 GeneratorT;

/*
 *  \class RandomNormal
 *  \brief Allows access to values from a normal distribution.
 *
 *  \tparam TypeT The element type
 */
template <typename TypeT>
class RandomNormal
{
public:
    /*
     *  \func Constructor
     *  \brief Sets up the distribution
     *
     *  \param seed The randomization seed
     *  \param mean The mean of the distribution
     *  \param standardDeviation The standard deviation of the distribution
     *  \param min The min acceptable value
     *  \param max The max acceptable value
     */
    RandomNormal(size_t seed,
                 double mean,
                 double standardDeviation,
                 TypeT min,
                 TypeT max) :
        mMin(min),
        mMax(max),
        mGenerator(seed),
        mDistribution(mean, standardDeviation)
    {
    }

    /*
     *  \func Constructor
     *  \brief Same as above but defaults min and max to -infinity, +infinity
     */
    RandomNormal(size_t seed,
                 double mean,
                 double standardDeviation) :
        RandomNormal(seed,
                     mean,
                     standardDeviation,
                     std::is_floating_point<TypeT>::value ?
                             -std::numeric_limits<TypeT>::max() :
                             std::numeric_limits<TypeT>::min(),
                     std::numeric_limits<TypeT>::max())
    {
    }

    /*
     *  \func Constructor
     *  \brief Same as about but randomizes the seed.
     */
    RandomNormal(double mean,
                 double standardDeviation,
                 TypeT min,
                 TypeT max) :
        RandomNormal(epoch(), mean, standardDeviation, min, max)
    {
    }

    /*
     *  \func Constructor
     *  \brief Same as about but randomizes the seed and defaults min and
     *         max to -infinity, +infinity
     */
    RandomNormal(double mean,
                 double standardDeviation) :
        RandomNormal(epoch(), mean, standardDeviation)
    {
    }

    /*
     *  \func Constructor
     *  \brief Same as about but sets the mean to 0, stddev to 1 and defaults
     *         the min and max to -infinity, +infinity
     */
    RandomNormal(size_t seed) :
        RandomNormal(seed, 0.0, 1.0)
    {
    }

    /*
     *  \func Constructor
     *  \brief Same as about but sets the mean to 0, stddev to 1, defaults
     *         the min and max to -infinity, +infinity, and randomizes the
     *         seed.
     */
    RandomNormal() :
        RandomNormal(epoch())
    {
    }

    /*
     *  \func getMean
     *  \brief Gets the mean of the distribution
     *
     *  \return The mean
     */
    double getMean() const
    {
        return mDistribution.mean();
    }

    /*
     *  \func getStandardDeviation
     *  \brief Gets the standard deviation of the distribution
     *
     *  \return The stadard deviation
     */
    double getStandardDeviation() const
    {
        return mDistribution.stddev();
    }

    /*
     *  \func getMin
     *  \brief Gets the min value of the distribution
     *
     *  \return The min
     */
    TypeT getMin() const
    {
        return mMin;
    }

    /*
     *  \func getMax
     *  \brief Gets the max value of the distribution
     *
     *  \return The max
     */
    TypeT getMax() const
    {
        return mMax;
    }

    /*
     *  \func Functor
     *  \brief Gets a single value from the distribution
     *
     *  \return The value.
     */
    TypeT operator()()
    {
        double value = mDistribution(mGenerator);
        while (value < mMin || value > mMax)
        {
            value = mDistribution(mGenerator);
        }

        if (std::is_integral<TypeT>::value)
        {
            value = std::round(value);
        }

        return static_cast<TypeT>(value);
    }

private:
    const double mMin;
    const double mMax;

    typedef typename std::conditional
            <std::is_floating_point<TypeT>::value,
             std::normal_distribution<TypeT>,
             std::normal_distribution<double>>::type DistributionT;
    GeneratorT mGenerator;
    DistributionT mDistribution;
};

/*
 *  \class RandomUniform
 *  \brief Allows access to values from a uniform distribution.
 *
 *  \tparam TypeT The element type
 */
template <typename TypeT>
class RandomUniform
{
public:
    /*
     *  \func Constructor
     *  \brief Sets up the distribution
     *
     *  \param seed The randomization seed
     *  \param min The min acceptable value
     *  \param max The max acceptable value
     */
    RandomUniform(size_t seed,
                  TypeT min,
                  TypeT max) :
        mGenerator(seed),
        mDistribution(min, max)
    {
    }

    /*
     *  \func Constructor
     *  \brief Same as about but randomizes the seed.
     */
    RandomUniform(TypeT min, TypeT max) :
        RandomUniform(epoch(), min, max)
    {
    }

    /*
     *  \func Constructor
     *  \brief Same as about but sets the defaults min and max to
     *         -infinity, +infinity
     */
    RandomUniform(size_t seed) :
        mGenerator(seed)
    {
    }

    /*
     *  \func Constructor
     *  \brief Same as about but randomizes the seed and defaults min and
     *         max to -infinity, +infinity
     */
    RandomUniform() :
        RandomUniform(epoch())
    {
    }

    /*
     *  \func Functor
     *  \brief Gets a single value from the distribution
     *
     *  \return The value.
     */
    TypeT operator()()
    {
        return mDistribution(mGenerator);
    }

private:
    GeneratorT mGenerator;
    typedef typename std::conditional
            <std::is_floating_point<TypeT>::value,
             std::uniform_real_distribution<TypeT>,
             std::uniform_int_distribution<TypeT>>::type DistributionT;
    DistributionT mDistribution;
};
}
}

#endif
