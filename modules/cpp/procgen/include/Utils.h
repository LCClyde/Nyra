/*
 * Copyright (c) 2018 Clyde Stanfield
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
#ifndef __NYRA_PROCGEN_UTILS_H__
#define __NYRA_PROCGEN_UTILS_H__

#include <limits>
#include <utility>
#include <nyra/math/Interpolate.h>
#include <nyra/math/Vector2.h>

namespace nyra
{
namespace procgen
{
/*
 *  \var DEFAULT_SIZE
 *  \brief The default size used to determine statistics of the noise.
 */
static const math::Vector2U DEFAULT_SIZE(1600, 900);

/*
 *  \func getMinMax
 *  \brief Gets the min and max of a noise function. This is not guaranteed
 *         to be the actual min/max as the values could go beyond these
 *         numbers at different resolutions..
 *
 *  \tparam NoiseT The noise class
 *  \param noise The noise to evaluate
 *  \return The min / max. First in min, second is max.
 */
template <typename NoiseT>
std::pair<double, double> getMinMax(const NoiseT& noise)
{
    std::pair<double, double> minMax(std::numeric_limits<double>::max(),
                                     -std::numeric_limits<double>::max());
    for (size_t y = 0; y < DEFAULT_SIZE.y; ++y)
    {
        for (size_t x = 0; x < DEFAULT_SIZE.x; ++x)
        {
            double value = noise(x, y);
            minMax.first = std::min(value, minMax.first);
            minMax.second = std::max(value, minMax.second);
        }
    }
    return minMax;
}

/*
 *  \func getValueAtPercent
 *  \brief Gets the value that is x% between min / max
 *
 *  \tparam NoiseT The noise class
 *  \param noise The noise to evaluate
 *  \param percent The desired percent from 0-1, 0 gives min, 1 gives max
 *  \return The value that represents the percent.
 */
template <typename NoiseT>
double getValueAtPercent(const NoiseT& noise,
                         double percent)
{
    const double scale = 4.0;
    const math::Vector2U reducedSize(DEFAULT_SIZE / scale);
    const size_t size = reducedSize.product();
    std::vector<double> values(size);

    for (size_t y = 0; y < reducedSize.y; ++y)
    {
        for (size_t x = 0; x < reducedSize.x; ++x)
        {
            values[y * reducedSize.x + x] = noise(x * scale, y * scale);
        }
    }
    std::sort(values.begin(), values.end());
    return values[static_cast<size_t>((size - 1) * percent)];
}
}
}

#endif
