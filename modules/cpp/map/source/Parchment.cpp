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
#include <nyra/map/Parchment.h>
#include <nyra/math/Interpolate.h>

namespace nyra
{
namespace map
{
//===========================================================================//
Parchment::Parchment(size_t seed) :
    Module(new algs::PerlinNoise(algs::FRACTAL_BROWNIAN_MOTION,
                                 0.01, 2.0, 0.5, 3, seed)),
    mMinMax(getMinMax()),
    mDelta(mMinMax.second - mMinMax.first)
{
}

//===========================================================================//
img::Color Parchment::calcPixel(double value)
{
    const double percent = (value - mMinMax.first) * mDelta;
    return math::linearInterpolate(img::Color(245, 222, 179),
                                   img::Color(232, 181, 85),
                                   percent);
}
}
}
