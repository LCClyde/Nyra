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
#include <nyra/map/LandMask.h>

namespace nyra
{
namespace map
{
//===========================================================================//
LandMask::LandMask(double waterPercent,
                   size_t seed) :
    mNoise(new algs::SimplexNoise(algs::FRACTAL_BROWNIAN_MOTION,
                                  0.001, 1.75, 0.5, 5, seed)),
    mWaterValue(mNoise.getValueAtPercent(waterPercent))
{
}

//===========================================================================//
img::Image LandMask::getImage(const math::Vector2U& size) const
{
    PixFunc func(std::bind(&LandMask::calcPixel,
                           this,
                           std::placeholders::_1));
    return mNoise.getImage(size, func);
}

//===========================================================================//
img::Color LandMask::calcPixel(double value) const
{
    return value < mWaterValue ?
                img::Color::BLACK : img::Color::WHITE;
}
}
}
