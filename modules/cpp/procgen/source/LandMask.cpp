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
#include <nyra/procgen/LandMask.h>
#include <nyra/procgen/Utils.h>

namespace nyra
{
namespace procgen
{
//===========================================================================//
LandMask::LandMask(double waterPercent,
                   size_t seed) :
    mNoise(algs::FRACTAL_BROWNIAN_MOTION,
           0.001, 1.75, 0.5, 5, seed),
    mWaterValue(getValueAtPercent(mNoise, waterPercent))
{
}

//===========================================================================//
img::Image LandMask::getImage(const math::Vector2U& size) const
{
    img::Image image(size);
    const math::Vector2F resolution(
            static_cast<double>(DEFAULT_SIZE.x) / size.x,
            static_cast<double>(DEFAULT_SIZE.y) / size.y);

    for (size_t y = 0; y < size.y; ++y)
    {
        for (size_t x = 0; x < size.x; ++x)
        {
            const double value =
                    mNoise(x * resolution.x, y * resolution.y);
            image(y, x) = value < mWaterValue ?
                    img::Color::BLACK : img::Color::WHITE;
        }
    }
    return image;
}
}
}
