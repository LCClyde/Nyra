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
#include <nyra/map/Water.h>
#include <nyra/img/Algs.h>
#include <nyra/math/Conversions.h>

namespace
{
//===========================================================================//
class WarpX
{
public:
    double operator()(double x, double y) const
    {
        return std::sin(nyra::math::degreesToRadians(x * 4.0)) * 2.0;
    }
};

//===========================================================================//
class WarpY
{
public:
    double operator()(double x, double y) const
    {
        return std::sin(nyra::math::degreesToRadians(y * 4.0)) * 2.0;
    }
};

//===========================================================================//
static const nyra::img::Color  WATER_DARK(  0,  47,  75, 255);
static const nyra::img::Color WATER_LIGHT( 64, 164, 223, 255);
}

namespace nyra
{
namespace map
{
//===========================================================================//
Water::Water(size_t seed) :
    mNoise(new algs::SimplexNoise(algs::FRACTAL_BROWNIAN_MOTION,
                                  0.01, 2.0, 0.5, 5, seed)),
    mHalfNoise(mNoise.getValueAtPercent(0.15))
{
}

//===========================================================================//
img::Image Water::getImage(const img::Image& landMask) const
{
    const img::Image edges = buildCoastEdgeMask(landMask);
    core::write(edges, "edges.png");

    img::Image waterMask = img::invert(landMask);
    img::Image coast = img::gaussianBlur(waterMask, 200);
    coast *= waterMask;
    coast *= img::invert(edges);

    return addColor(coast) * waterMask;
}

//===========================================================================//
img::Image Water::buildCoastEdgeMask(const img::Image& landMask) const
{
    // Create a line 4 pixels out
    img::Image dilate = img::dilate(landMask, 4);
    img::Image edges = img::edgeDetect(dilate, 50.0);

    // Create a line 8 pixels out
    dilate = img::dilate(landMask, 8);
    edges +=  img::edgeDetect(dilate, 50);

    // Break up the lines
    img::Image randMask = mNoise.getImage(landMask.getSize());
    randMask = img::threshold(randMask, mHalfNoise);
    edges *= randMask;

    // Warp the lines slightly to make them less uniform
    edges = img::warp(edges, WarpX(), WarpY());
    return edges;
}

//===========================================================================//
img::Image Water::addColor(const img::Image& input) const
{
    img::Image colored(input.getSize());
    for (size_t ii = 0; ii < input.getSize().product(); ++ii)
    {
        colored(ii) = math::linearInterpolate(
                WATER_LIGHT, WATER_DARK, input(ii).r / 255.0);
    }
    return colored;
}
}
}
